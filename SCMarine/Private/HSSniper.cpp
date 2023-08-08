// Fill out your copyright notice in the Description page of Project Settings.


#include "HSSniper.h"
#include "Kismet/GameplayStatics.h"
#include "SCMarine/SCMEnemy.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/DecalComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "SCMarine/SCMarinePlayerController.h"
#include "SCMarine/SCMPlayerCharacter.h"

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

void AHSSniper::PrimaryFire(APlayerController* PController, AActor* PossessedActor)
{

	if ((!bIsFiring) && (CurrentMag > 0) && (!bIsReloading))
	{
		FVector CameraLocation;
		FRotator CameraRotation;
		TArray<FHitResult> Hits;
		TSet<AActor*> HitActors;
		UWorld* World = PossessedActor->GetWorld();

		APlayerController* PlayerController = Cast<APlayerController>
			(UGameplayStatics::GetPlayerController(GetWorld(), 0));;
		PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

		StartFiring();
		CurrentMag--;
		UpdateMagString();
		PlayFireAnimation(PossessedActor);

		FVector Start = CameraLocation;
		FVector End = Start + (CameraRotation.Vector() * Range);

		FCollisionQueryParams TraceParams;
		TraceParams.AddIgnoredActor(PossessedActor);		// don't shoot self LOL
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


						UGameplayStatics::ApplyPointDamage(Enemy, Damage, HitFromDirection, Hit, PlayerController, PossessedActor, nullptr);
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
			AltFire(PController, PossessedActor);
		}
	}
}

void AHSSniper::AltFire(APlayerController* PController, AActor* PossessedActor)
{
	ASCMarinePlayerController* SCMPController = Cast<ASCMarinePlayerController>(PController);
	ASCMPlayerCharacter* PlayerChar = Cast<ASCMPlayerCharacter>(PossessedActor);

	if (SCMPController)
	{
		if (ScopedIn)
		{
			SCMPController->ScopeOut();
			ScopedIn = false;
			PlayerChar->CamZoomOut();
			//SniperNightvisionOff(PossessedActor);
			PlayerChar->TurnOffNightvision();
		}
		else
		{
			SCMPController->ScopeIn();
			ScopedIn = true;
			PlayerChar->CamZoomIn();
			if (NightvisionOn)
			{
				PlayerChar->TurnOnNightvision();
				//SniperNightvisionOn(PossessedActor);
			}
		}
	}

}

void AHSSniper::ReloadWeapon(AActor* PossessedActor)
{
	Super::ReloadWeapon(PossessedActor);
	
	if ((CurrentAmmo == 0) || (CurrentMag == MaxMag)) { return; }
	
	if (ScopedIn)
	{
		AltFire(GetWorld()->GetFirstPlayerController(), PossessedActor);
	}
}

void AHSSniper::SniperNightvisionOn(AActor* PossessedActor)
{
	ASCMPlayerCharacter* PlayerChar = Cast<ASCMPlayerCharacter>(PossessedActor);
	if (PlayerChar)
	{
		PlayerChar->TurnOnNightvision();
		NightvisionOn = true;
	}
}

void AHSSniper::SniperNightvisionOff(AActor* PossessedActor)
{
	ASCMPlayerCharacter* PlayerChar = Cast<ASCMPlayerCharacter>(PossessedActor);
	if (PlayerChar)
	{
		PlayerChar->TurnOffNightvision();
		NightvisionOn = false;
	}
}
