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
	FString GunshotPath = R"('/Game/Models/Guns/3_HellfireShotgun/SFX/Hellfire_ShotgunFIRE_02.Hellfire_ShotgunFIRE_02')";
	FString ImpactDecalPath = R"('/Game/Decals/bullet_hole_1_Mat.bullet_hole_1_Mat')";
	virtual void PrimaryFire(APlayerController* PController, AActor* PossessedActor) override;

};
