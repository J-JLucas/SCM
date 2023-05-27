// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SCMProjectileWeapon.h"
#include "PRocketLauncher.generated.h"

/**
 * 
 */
UCLASS()
class SCMARINE_API APRocketLauncher : public ASCMProjectileWeapon
{
	GENERATED_BODY()

public:
	APRocketLauncher();

	virtual void BeginPlay() override;

	FString GunshotPath = R"('/Game/Models/Guns/6_RocketLauncher/SFX/Marauder_AttackLaunch3.Marauder_AttackLaunch3')";

	virtual void PrimaryFire(APlayerController* PController, AActor* PossessedActor) override;
};
