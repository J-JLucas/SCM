// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/SCMExplosion.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"
#include "Enemy/EnemyUltra.h"


// Sets default values
ASCMExplosion::ASCMExplosion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SphereComponent->SetSphereRadius(500.0f);
	RootComponent = SphereComponent;
	InitialLifeSpan = 0.3f;
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ASCMExplosion::OnOverlapBegin);
	//ExplosionParticles = CreateDefaultSubobject<UParticleSystem>(TEXT("ExplosionEffect"));
	//ExplosionParticles->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ASCMExplosion::BeginPlay()
{
	Super::BeginPlay();
	
	if (ExplosionSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation(), 1.0f, FMath::RandRange(0.9f, 1.1f), 0.0f);
	}
	DrawDebugSphere(GetWorld(), GetActorLocation(), SphereComponent->GetScaledSphereRadius(), 50, FColor::Cyan, false, 1.0f);

}

void ASCMExplosion::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// There seems to be a race condition near the origin of explosion,
	// despite ignoring members of AffectedActors, sometimes k components of same actor are "damaged"

	if (OtherActor != this && !AffectedActors.Contains(OtherActor))
	{
		AffectedActors.Add(OtherActor);		// Don't Interact with this Actor again

		FVector ExplosionLocation = GetActorLocation();
		FVector OtherActorLocation = OtherActor->GetActorLocation();
		FVector ExplosionDirection = (OtherActorLocation - ExplosionLocation).GetSafeNormal();

		// falloff is significant, added +100.0f beyond the collisionsphere to "reduce" damage falloff
		float DamageRadius = (SphereComponent->GetScaledSphereRadius() + 100.0f);

		
		AEnemyUltra* Ultra = Cast<AEnemyUltra>(OtherActor);
		if (Ultra)	// don't push the ultra around
		{
			UGameplayStatics::ApplyRadialDamage(GetWorld(), DamageValue, ExplosionLocation, DamageRadius, nullptr, TArray<AActor*>(), this, false, false);
			return;
		}
		

		ACharacter* Target = Cast<ACharacter>(OtherActor);
		if (Target)
		{
			Target->LaunchCharacter(ExplosionDirection * 1800.0f + FVector(0.0f, 0.0f, 500.0f), true, true);
			
			// Deal Explosive Radial Damage
			UGameplayStatics::ApplyRadialDamage(GetWorld(), DamageValue, ExplosionLocation, DamageRadius, nullptr,
				TArray<AActor*>(), GetInstigator(), GetInstigatorController(),
				false, ECollisionChannel::ECC_Visibility
			);
		
		}
	}
}

// Called every frame
void ASCMExplosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

