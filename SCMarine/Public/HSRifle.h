// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SCMHitScanWeapon.h"
#include "HSRifle.generated.h"

/**
 * 
 */
UCLASS()
class SCMARINE_API AHSRifle : public ASCMHitScanWeapon
{
	GENERATED_BODY()
	
public:

	AHSRifle();
	virtual void BeginPlay() override;

	// Path to gunshot sfx, must call SetGunshotSFX(GunshotPath) in constructor
	

	//FString GunshotPath = R"('/Game/Models/Guns/4_GaussRifle/SFX/SingleFull2.SingleFull2')";
	FString ImpactDecalPath = R"('/Game/Decals/bullet_hole_1_Mat.bullet_hole_1_Mat')";
	FString BloodEffectPath = R"('/Game/Decals/NS_BloodEffect.NS_BloodEffect')";
	FString GunshotPath = R"('/Game/Models/Guns/4_GaussRifle/SFX/SingleFullDeagMix.SingleFullDeagMix')";
};
