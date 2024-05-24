// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/SCMHitScanWeapon.h"
#include "Enemy/SCMEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/DecalComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Perception/AISense_Damage.h"
#include "AIController.h"


ASCMHitScanWeapon::ASCMHitScanWeapon()
	:Super()
{
}

void ASCMHitScanWeapon::SetImpactDecal(FString Path)
{
	ImpactDecal = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, *Path));
	if (ImpactDecal == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load ImpactDecal"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("loaded ImpactDecal successfully"));
	}





}

void ASCMHitScanWeapon::SetBloodDecal(FString Path)
{ 
	BloodDecal = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, *Path));
	if (BloodDecal == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load BloodDecal"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("loaded BloodDecal successfully"));
	}
}

void ASCMHitScanWeapon::SetBloodEffect(FString Path)
{
	BloodEffect = Cast<UNiagaraSystem>(StaticLoadObject(UNiagaraSystem::StaticClass(), nullptr, *Path));
	if (BloodEffect == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load BloodEffect"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("loaded BloodEffect successfully"));
	}
}

void ASCMHitScanWeapon::TraceForward()
{
	
	FVector CameraLocation;
	FRotator CameraRotation;
	FHitResult Hit;
	UWorld* World = PlayerChar->GetWorld();

	PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

	FVector Start = CameraLocation;
	FVector End = Start + (CameraRotation.Vector() * Range);

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

			// Check For Headshot
			FString ComponentName = Hit.Component->GetName();
			if (ComponentName == "HeadshotCollision")
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, "BOOM HEADSHOT!!!!!");
				Damage = Damage * 2.0f;
			}

			UGameplayStatics::ApplyPointDamage(Enemy, Damage,HitFromDirection, Hit, PlayerController, PlayerChar, nullptr);


			//UAISense_Damage::ReportDamageEvent(this, Enemy, PlayerController, Damage, Hit.ImpactPoint, Hit.ImpactPoint);
			
			
			//UNiagaraFunctionLibrary::SpawnSystemAtLocation(World, BloodEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());

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
			FRotator DecalRotation = UKismetMathLibrary::MakeRotFromX(DecalRotationVec)*-1.0f;
			USceneComponent* AttachComponent = Hit.GetComponent(); // The component to which the decal will be attached

			float LifeSpan = 10.0f;
			UDecalComponent* BulletDecal = UGameplayStatics::SpawnDecalAttached(ImpactDecal, FVector(8.0f,8.0f,8.0f), AttachComponent, NAME_None, Hit.Location, DecalRotation, EAttachLocation::KeepWorldPosition, LifeSpan );
			BulletDecal->SetFadeScreenSize(0.0f);
		}
	}
}

void ASCMHitScanWeapon::PrimaryFire()
{
	if ((!bIsFiring) && (CurrentMag > 0) && (!bIsReloading))
	{
		Super::PrimaryFire();
		StartFiring();
		PlayFireAnimation();
		TraceForward();
	}
}

