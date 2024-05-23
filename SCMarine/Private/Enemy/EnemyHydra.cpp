// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyHydra.h"
#include "HealthComponent.h"
#include "Weapons/SCMProjectile.h"
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

void AEnemyHydra::HydraRangedAttack(FRotator TargetAngle)
{

	FVector ForwardVector = GetActorForwardVector();
	float SpawnDistance = 300.f;
	FVector SpawnLocation = GetActorLocation() + (ForwardVector * SpawnDistance);
	SpawnLocation.Z += 80.0f;

	// Calculate the tilt angle in degrees
	//float TiltAngle = -5.0f; // Adjust this value to control the amount of tilt
	//float TiltAngle = 0.0f; // Adjust this value to control the amount of tilt
	//FRotator SpawnRotation = GetActorRotation() + FRotator(TiltAngle, 0.0f, 0.0f);
	FTransform SpawnTransform(TargetAngle, SpawnLocation);

	// Spawn new SlimeProjectile
	ASCMProjectile* Projectile = GetWorld()->SpawnActorDeferred<ASCMProjectile>(SCMProjectileClass, SpawnTransform);

	Projectile->GetProjectileMovementComponent()->InitialSpeed = 4500.f;
	Projectile->FinishSpawning(SpawnTransform);

}
