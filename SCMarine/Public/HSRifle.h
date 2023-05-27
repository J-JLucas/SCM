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
	//FString GunshotPath = R"('/Game/Models/Guns/4_GaussRifle/SFX/RifleExp.RifleExp')";
	FString GunshotPath = R"('/Game/Models/Guns/4_GaussRifle/SFX/sc1MarineFire.sc1MarineFire')";
};
