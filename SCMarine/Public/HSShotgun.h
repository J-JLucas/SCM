// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SCMHitScanWeapon.h"
#include "HSShotgun.generated.h"

/**
 * 
 */
UCLASS()
class SCMARINE_API AHSShotgun : public ASCMHitScanWeapon
{
	GENERATED_BODY()

public:

	AHSShotgun();

	virtual void BeginPlay() override;

	// Path to gunshot sfx, must call SetGunshotSFX(GunshotPath) in constructor
	FString GunshotPath = R"('/Game/Models/Guns/3_Shotgun/SFX/Hellfire_Shotgun_02.Hellfire_Shotgun_02')";

};
