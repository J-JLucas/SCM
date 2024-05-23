// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/HSSniper.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy/SCMEnemy.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/DecalComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
//#include "SCMarinePlayerController.h"
//#include "SCMPlayerCharacter.h"

AHSSniper::AHSSniper()
	:Super()
{
	SetGunshotSFX(GunshotPath);
	SetImpactDecal(ImpactDecalPath);
	SetBloodEffect(BloodEffectPath);
	FireRate = 1.1f;
	ReloadRate = 3.0f;
	MaxAmmo = 50.0f;
	CurrentAmmo = 0.0f;
	MaxMag = 5;
	CurrentMag = 5;
	Name = FText::FromString("HEV 'COMMANDO' RIFLE");
}

void AHSSniper::BeginPlay()
{
	Super::BeginPlay();
	SetDamageAmount(150.0f);
	Range = 15000.0f;
	bPiercing = true;
}

void AHSSniper::PrimaryFire()
{

	if ((!bIsFiring) && (CurrentMag > 0) && (!bIsReloading))
	{
		FVector CameraLocation;
		FRotator CameraRotation;
		TArray<FHitResult> Hits;
		TSet<AActor*> HitActors;
		UWorld* World = PlayerChar->GetWorld();

		PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

		StartFiring();
		CurrentMag--;
		UpdateMagString();
		PlayFireAnimation();

		FVector Start = CameraLocation;
		FVector End = Start + (CameraRotation.Vector() * Range);

		FCollisionQueryParams TraceParams;
		TraceParams.AddIgnoredActor(PlayerChar);		// don't shoot self LOL
		bool bHit = World->LineTraceMultiByChannel(Hits, Start, End, ECollisionChannel::ECC_GameTraceChannel2, TraceParams);
		DrawDebugLine(World, Start, End, FColor::Purple, false, 5.0f);

		for (const FHitResult& Hit : Hits)
		{
				AActor* OtherActor = Hit.GetActor();
				if (OtherActor && !HitActors.Contains(OtherActor))	// Don't damage enemy for each bodypart bullet passes through
				{
					HitActors.Add(OtherActor);
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
						UNiagaraFunctionLibrary::SpawnSystemAtLocation(World, BloodEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());

					}
					else
					{
						// spawn generic bullethole decal
						FVector DecalRotationVec = (Hit.ImpactNormal);
						DecalRotationVec.Normalize();
						FRotator DecalRotation = UKismetMathLibrary::MakeRotFromX(DecalRotationVec) * -1.0f;
						USceneComponent* AttachComponent = Hit.GetComponent(); // The component to which the decal will be attached


						float LifeSpan = 30.0f;
						//UDecalComponent* BulletDecal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), ImpactDecal, FVector(6.0f, 6.0f, 6.0f), Hit.Location, DecalRotation, LifeSpan);
						UDecalComponent* BulletDecal = UGameplayStatics::SpawnDecalAttached(ImpactDecal, FVector(5.0f, 5.0f, 5.0f), AttachComponent, NAME_None, Hit.Location, DecalRotation, EAttachLocation::KeepWorldPosition, LifeSpan);
						BulletDecal->SetFadeScreenSize(0.0f);
					}
				}
		}
		if (ScopedIn)
		{
			AltFire();
		}
	}
}

void AHSSniper::AltFire()
{
	if (PlayerController)
	{
		if (ScopedIn)
		{
			PlayerController->ScopeOut();
			ScopedIn = false;
			PlayerChar->CamZoomOut();
			PlayerChar->TurnOffNightvision();
		}
		else
		{
			PlayerController->ScopeIn();
			ScopedIn = true;
			PlayerChar->CamZoomIn();
			if (NightvisionOn)
			{
				PlayerChar->TurnOnNightvision();
			}
		}
	}

}

void AHSSniper::ReloadWeapon()
{
	Super::ReloadWeapon();
	
	if ((CurrentAmmo == 0) || (CurrentMag == MaxMag)) { return; }
	
	if (ScopedIn)
	{
		AltFire();
	}
}

void AHSSniper::SniperNightvisionOn()
{
	if (PlayerChar)
	{
		PlayerChar->TurnOnNightvision();
		NightvisionOn = true;
	}
}

void AHSSniper::SniperNightvisionOff()
{
	if (PlayerChar)
	{
		PlayerChar->TurnOffNightvision();
		NightvisionOn = false;
	}
}
