// Fill out your copyright notice in the Description page of Project Settings.


#include "SCMProjectile.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

// Sets default values
ASCMProjectile::ASCMProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxComponent->SetBoxExtent(FVector(10.0f, 10.0f, 10.0f));
	BoxComponent->SetCollisionProfileName(FName("Projectile"));
	
	// Listen to the OnComponentHit event by binding it to the function
	BoxComponent->OnComponentHit.AddDynamic(this, &ASCMProjectile::OnHit);
	RootComponent = BoxComponent;

	PrjMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Projectile Mesh"));
	check(PrjMesh != nullptr);

	PrjMesh->SetupAttachment(BoxComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->SetUpdatedComponent(BoxComponent);
	ProjectileMovement->InitialSpeed = 3000.0f;
	ProjectileMovement->MaxSpeed = 3000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
	
	// Delete the projectile after 4 seconds
	InitialLifeSpan = 3.0f;
	
}

// Called when the game starts or when spawned
void ASCMProjectile::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASCMProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASCMProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (ImpactSound)
	{
		//supply pitch multiplier factor between random range of specified floats
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), 1.0f, FMath::RandRange(0.9f, 1.1f), 0.0f);
	}

	ACharacter* Target = Cast<ACharacter>(OtherActor);

	if (Target)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, "Hit an Actor");
		UGameplayStatics::ApplyDamage(OtherActor, Damage, GetInstigatorController(), this, nullptr);
		if (DamageSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, DamageSound, GetActorLocation(), 1.0f, FMath::RandRange(0.9f, 1.1f), 0.0f);
		}
	}

	if (HitParticles)
	{
		//FVector Location = FVector::ZeroVector;;
		FRotator Rotation = FRotator::ZeroRotator;;
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticles, GetActorLocation(), Rotation, true);
	}
	else
	{
		// Particle effect never despawns...
		//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticles, GetActorTransform());
	}

	Destroy();
}

void ASCMProjectile::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovement->Velocity = ShootDirection * ProjectileMovement->InitialSpeed;

}

