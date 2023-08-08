// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SCMHitScanWeapon.h"
#include "HSSniper.generated.h"

/**
 * 
 */
UCLASS()
class SCMARINE_API AHSSniper : public ASCMHitScanWeapon
{
	GENERATED_BODY()
	
protected:

public:

	AHSSniper();

	virtual void BeginPlay() override;

	void PrimaryFire(APlayerController* PController, AActor* PossessedActor);
	void AltFire(APlayerController* PController, AActor* PossessedActor);
	void ReloadWeapon(AActor* PossessedActor);
	void SniperNightvisionOn(AActor* PossessedActor);
	void SniperNightvisionOff(AActor* PossessedActor);

	bool ScopedIn { false };
	bool NightvisionOn { false };

	// Path to gunshot sfx, must call SetGunshotSFX(GunshotPath) in constructor
	FString GunshotPath = R"('/Game/Models/Guns/5_SniperRifle/SFX/ReynorNovaMix.ReynorNovaMix')";
	FString ImpactDecalPath = R"('/Game/Decals/bullet_hole_1_Mat.bullet_hole_1_Mat')";
	FString BloodEffectPath = R"('/Game/Decals/NS_BloodEffect.NS_BloodEffect')";

	FORCEINLINE bool GetIsScopedIn() { return ScopedIn; }
	FORCEINLINE bool GetIsNightvisionOn() { return NightvisionOn; }
	FORCEINLINE void SetIsNightvisionOn(bool Status) { NightvisionOn = Status; }
};
