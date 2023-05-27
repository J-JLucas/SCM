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

	// Path to gunshot sfx, must call SetGunshotSFX(GunshotPath) in constructor
	FString GunshotPath = R"('/Game/Models/Guns/5_SniperRifle/SFX/ReynorNovaMix.ReynorNovaMix')";

};
