// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SCMProjectileWeapon.h"
#include "PFlameThrower.generated.h"

/**
 * 
 */
UCLASS()
class SCMARINE_API APFlameThrower : public ASCMProjectileWeapon
{
	GENERATED_BODY()
	
public:
	APFlameThrower();

	virtual void BeginPlay() override;

	FString GunshotPath = R"('/Game/Models/Guns/7_FlameThrower/SFX/FlameThrower_Fire.FlameThrower_Fire')";

};
