// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/SCMProjectileWeapon.h"
#include "Weapons/SCMProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"



void ASCMProjectileWeapon::PrimaryFire(APlayerController* PController, AActor* PossessedActor)
{
	if ((!bIsFiring) && (CurrentMag > 0) && (!bIsReloading))
	{
		Super::PrimaryFire(PController, PossessedActor);
		StartFiring();
		//PlayGunshotSFX(PossessedActor);
		PlayFireAnimation(PossessedActor);
		if (!SCMProjectileClass)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "No Projectile Class");
			return;
		}

		// Get the camera transform.
		FVector CameraLocation;
		FRotator CameraRotation;
		PController->GetPlayerViewPoint(CameraLocation, CameraRotation);

		// Set MuzzleOffset to spawn projectiles slightly in front of the camera.
		MuzzleOffset.Set(200.0f, 0.0f, 0.0f);

		// Transform MuzzleOffset from camera space to world space.
		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
		FRotator MuzzleRotation = CameraRotation;


		FVector ForwardVector = GetActorForwardVector();
		float SpawnDistance = 100.f;
		FVector SpawnLocation = GetActorLocation() + (ForwardVector * SpawnDistance);
		FTransform SpawnTransform(GetActorRotation(), SpawnLocation);

		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			// Spawn the projectile at the muzzle.
			ASCMProjectile* Projectile = World->SpawnActor<ASCMProjectile>(SCMProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				// Set the projectile's initial trajectory.
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
			}
		}
	}
}