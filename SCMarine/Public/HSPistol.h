// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SCMHitScanWeapon.h"
#include "HSPistol.generated.h"

/**
 * 
 */
UCLASS()
class SCMARINE_API AHSPistol : public ASCMHitScanWeapon
{
	GENERATED_BODY()
	
public:

	AHSPistol();

	// Path to gunshot sfx, must call SetGunshotSFX(GunshotPath) in constructor
	FString GunshotPath = R"('/Game/Models/Guns/2_Pistol/SFX/deagle.deagle')";
};
