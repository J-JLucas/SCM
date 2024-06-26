// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/HSShotgun.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy/SCMEnemy.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/DecalComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"


AHSShotgun::AHSShotgun()
	:Super()
{
	SetImpactDecal(ImpactDecalPath);
	SetBloodEffect(BloodEffectPath);
	FireRate = 0.35f;
	ReloadRate = 2.0f;
	MaxAmmo = 100.0f;
	CurrentAmmo = 0.0f;
	MaxMag = 9;
	CurrentMag = 9;
	Name = FText::FromString("'HELLFIRE' SHOTGUN");
}

void AHSShotgun::BeginPlay()
{
	Super::BeginPlay();
	SetDamageAmount(6.0f);
}

void AHSShotgun::PrimaryFire()
{

	if ((!bIsFiring) && (CurrentMag > 0) && (!bIsReloading))
	{
		//Super::PrimaryFire(PController, PossessedActor);
		FVector CameraLocation;
		FRotator CameraRotation;
		FHitResult Hit;
		UWorld* World = PlayerChar->GetWorld();
		int32 ShotCount = 10;

		PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

		StartFiring();
		CurrentMag--;
		UpdateMagString();
		PlayFireAnimation();

		// fire ShotCount Pellets (algie from ChatGPT based off of quake sourcecode)
		for (int32 i = 0; i < ShotCount; i++)
		{
			float Spread = 17.0f;
			float SpreadValue = FMath::RandRange(0.0f, Spread);

			FVector Start = CameraLocation;
			FVector ShootDir = CameraRotation.Vector();

			// Generate random angles for cone spread
			float ConeHalfAngle = FMath::DegreesToRadians(SpreadValue * 0.5f);
			float RandomPitch = FMath::FRandRange(-ConeHalfAngle, ConeHalfAngle);
			float RandomYaw = FMath::FRandRange(-ConeHalfAngle, ConeHalfAngle);

			// Apply random pitch and yaw to shoot direction
			FRotator ShootRot = FRotator(ShootDir.Rotation().Pitch + FMath::RadiansToDegrees(RandomPitch), ShootDir.Rotation().Yaw + FMath::RadiansToDegrees(RandomYaw), 0.0f);
			FVector SpreadDirection = ShootRot.Vector();

			FVector End = Start + (SpreadDirection * Range);

			FCollisionQueryParams TraceParams;
			TraceParams.AddIgnoredActor(PlayerChar);		// don't shoot self LOL
			bool bHit = World->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_GameTraceChannel3, TraceParams);

			DrawDebugLine(World, Start, End, FColor::Purple, false, 5.0f);

			if (bHit)
			{
				DrawDebugBox(World, Hit.ImpactPoint, FVector(5, 5, 5), FColor::Emerald, false, 5.0f);

				ASCMEnemy* Enemy = Cast<ASCMEnemy>(Hit.GetActor());
				if (Enemy)
				{
					float Damage = GetDamageAmount();
					FVector HitFromDirection = (Start - End).GetSafeNormal();
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, "Hit Enemy");

					// Check for headshot
					FString ComponentName = Hit.Component->GetName();
					if (ComponentName == "HeadshotCollision")
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, "BOOM HEADSHOT!!!!!");
						Damage = Damage * 2.0f;
					}
					else
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Bodyshot");
					}


					UGameplayStatics::ApplyPointDamage(Enemy, Damage, HitFromDirection, Hit, PlayerController, PlayerChar, nullptr);
					Enemy->LaunchCharacter(-HitFromDirection * ImpulseStrength + FVector(0.0f, 0.0f, 0.0f), false, false);
					UNiagaraComponent* SpawnedEffect = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
						World,
						BloodEffect,
						Hit.ImpactPoint,
						Hit.ImpactNormal.Rotation(),
						FVector(1.0f),
						true,           // Whether the system should auto destroy when finished
						true,           // Should the system be auto-activated
						ENCPoolMethod::AutoRelease,  // Pooling method: AutoRelease back to pool
						true            // Whether to perform a pre-cull check
					);
				}
				else
				{
					// spawn generic bullethole decal
					FVector DecalRotationVec = (Hit.ImpactNormal);
					DecalRotationVec.Normalize();
					FRotator DecalRotation = UKismetMathLibrary::MakeRotFromX(DecalRotationVec) * -1.0f;
					USceneComponent* AttachComponent = Hit.GetComponent(); // The component to which the decal will be attached


					float LifeSpan = 10.0f;
					//UDecalComponent* BulletDecal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), ImpactDecal, FVector(6.0f, 6.0f, 6.0f), Hit.Location, DecalRotation, LifeSpan);
					UDecalComponent* BulletDecal = UGameplayStatics::SpawnDecalAttached(ImpactDecal, FVector(5.0f, 5.0f, 5.0f), AttachComponent, NAME_None, Hit.Location, DecalRotation, EAttachLocation::KeepWorldPosition, LifeSpan);
					BulletDecal->SetFadeScreenSize(0.0f);
				}
			}
		}
	}
}