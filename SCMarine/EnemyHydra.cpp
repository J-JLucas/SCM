// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyHydra.h"
#include "HealthComponent.h"
#include "SCMProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"


AEnemyHydra::AEnemyHydra()
	:Super()
{
	float MaxHealth = (200.0f);
	// Init Health Component
	HealthComponent->SetMaxHealth(MaxHealth);

	// Find the blueprint class reference for ASCMProjectile
	static ConstructorHelpers::FObjectFinder<UClass> ProjectileBlueprint(TEXT("/Game/Blueprints/Guns/BP_SlimePrj.BP_SlimePrj_C"));
	// PATH format: TEXT("/Game/Blueprints/Guns/BP_SlimePrj.BP_SlimePrj_C")
	if (ProjectileBlueprint.Object)
	{
		SCMProjectileClass = ProjectileBlueprint.Object;
	}

}

void AEnemyHydra::HydraRangedAttack()
{


	FVector ForwardVector = GetActorForwardVector();
	float SpawnDistance = 300.f;
	FVector SpawnLocation = GetActorLocation() + (ForwardVector * SpawnDistance);
	SpawnLocation.Z += 250.0f;
	
	// Calculate the tilt angle in degrees
	float TiltAngle = -5.0f; // Adjust this value to control the amount of tilt
	FRotator SpawnRotation = GetActorRotation() + FRotator(TiltAngle, 0.0f, 0.0f);
	//FTransform SpawnTransform(GetActorRotation(), SpawnLocation);
	FTransform SpawnTransform(SpawnRotation, SpawnLocation);

	// Spawn new SlimeProjectile
	ASCMProjectile* Projectile = GetWorld()->SpawnActorDeferred<ASCMProjectile>(SCMProjectileClass, SpawnTransform);

	Projectile->GetProjectileMovementComponent()->InitialSpeed = 2500.f;
	Projectile->FinishSpawning(SpawnTransform);

}
