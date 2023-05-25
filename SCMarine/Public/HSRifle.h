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

	// Path to gunshot sfx, must call SetGunshotSFX(GunshotPath) in constructor
	FString GunshotPath = R"('/Game/Models/Guns/Rifle/SFX/deagle.deagle')";
	
	//FString GunshotPath = R"('/Game/Models/Guns/Rifle/SFX/RifleExp.RifleExp')";
	//FString GunshotPath = R"('/Game/Models/Guns/Rifle/SFX/SingleShotRifle.SingleShotRifle')";
	//FString GunshotPath = R"('/Game/Models/Guns/Rifle/SFX/sc1MarineFire.sc1MarineFire')";
};
