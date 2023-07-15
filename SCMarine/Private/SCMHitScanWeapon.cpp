// Fill out your copyright notice in the Description page of Project Settings.


#include "SCMHitScanWeapon.h"
#include "SCMarine/SCMEnemy.h"
#include "SCMarine/SCMPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/DecalComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/PrimitiveComponent.h"

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

void ASCMHitScanWeapon::TraceForward(APlayerController* PController, AActor* PossessedActor)
{
	
	FVector CameraLocation;
	FRotator CameraRotation;
	FHitResult Hit;
	UWorld* World = PossessedActor->GetWorld();

	APlayerController* PlayerController = Cast<APlayerController>
		(UGameplayStatics::GetPlayerController(GetWorld(), 0));;
	PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

	FVector Start = CameraLocation;
	FVector End = Start + (CameraRotation.Vector() * Range);

	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(PossessedActor);		// don't shoot self LOL
	bool bHit = World->LineTraceSingleByChannel(Hit, Start, End, ECC_Pawn, TraceParams);

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
			UGameplayStatics::ApplyPointDamage(Enemy, Damage,HitFromDirection, Hit, PlayerController, PossessedActor, nullptr);
			//Enemy->LaunchCharacter(-HitFromDirection * ImpulseStrength + FVector(0.0f, 0.0f, 0.0f), false, false);
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(World, BloodEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
			
			// Removed due to horrible performance,
			// Decals are bad, need to learn about 
			// RVT (runtime virtual texture) or render target capture to "paint" directly to the texture of a model 
			//Enemy->SpawnBloodEffectEvent(Hit.ImpactPoint, Hit.ImpactNormal);
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

void ASCMHitScanWeapon::PrimaryFire(APlayerController* PController, AActor* PossessedActor)
{
	if ((!bIsFiring) && (CurrentMag > 0) && (!bIsReloading))
	{
		Super::PrimaryFire(PController, PossessedActor);
		StartFiring();
		PlayFireAnimation(PossessedActor);
		PlayGunshotSFX(PossessedActor);
		TraceForward(PController, PossessedActor);
	}
}

