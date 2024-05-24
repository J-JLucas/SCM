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


// fires slime projectile at player
void AEnemyHydra::RangedAttack()
{
	FVector ForwardVector = GetActorForwardVector();
	float SpawnDistance = 300.f;
	FVector SpawnLocation = GetActorLocation() + (ForwardVector * SpawnDistance);
	SpawnLocation.Z += 80.0f;
	FRotator TargetAngle = FindLookAtRotation(GetActorLocation() + FVector(0.0f,0.0f, 40.0f), GetPlayerLocation());
	
	FTransform SpawnTransform(TargetAngle, SpawnLocation);
	ASCMProjectile* Projectile = GetWorld()->SpawnActorDeferred<ASCMProjectile>(SCMProjectileClass, SpawnTransform);

	if (Projectile)
	{
		// Play attack montage
		Super::RangedAttack();

		Projectile->GetProjectileMovementComponent()->InitialSpeed = 4500.f;
		Projectile->FinishSpawning(SpawnTransform);
	}
}
