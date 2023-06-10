// Fill out your copyright notice in the Description page of Project Settings.


#include "SCMExplosion.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "SCMarine/SCMPlayerCharacter.h"
#include "SCMarine/SCMEnemy.h"


// Sets default values
ASCMExplosion::ASCMExplosion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SphereComponent->SetSphereRadius(700.0f);
	RootComponent = SphereComponent;
	InitialLifeSpan = 2.0f;

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
	SphereComponent->OnComponentHit.AddDynamic(this, &ASCMExplosion::OnHit);
}

void ASCMExplosion::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	
	if (OtherActor != this)
	{
		FVector ExplosionLocation = GetActorLocation();
		float ExplosionForce = 5000.0f; // Adjust the force as needed
		float ExplosionRadius = 1000.0f;

		//OtherComp->AddRadialForce(ExplosionLocation, ExplosionForce, ExplosionRadius, ERadialImpulseFalloff::RIF_Linear, true);
		ASCMEnemy* Enemy = Cast<ASCMEnemy>(OtherActor);
		if (Enemy)
		{
			Enemy->LaunchCharacter(FVector(0.0f, 0.0f, 3000.0f), false, false);
		}
		
		//ASCMPlayerCharacter* Player = Cast<ASCMPlayerCharacter>(OtherActor);


	}
}

// Called every frame
void ASCMExplosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//float r = SphereComponent->GetScaledSphereRadius();
	//FVector CurrentScale = SphereComponent->GetComponentScale();
	//CurrentScale.X *= DeltaTime;
	//CurrentScale.Y *= DeltaTime;
	//CurrentScale.Z *= DeltaTime;
	//(CurrentScale.X)++;
	//(CurrentScale.Y)++;
	//(CurrentScale.Z)++;
	//SphereComponent->SetSphereRadius(r);
	//r = FMath::Clamp(CurrentScale, 1.0f, 2.0f);
	//SphereComponent->SetWorldScale3D(CurrentScale);
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Explosion Tick");
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::SanitizeFloat(CurrentScale.X));

}

