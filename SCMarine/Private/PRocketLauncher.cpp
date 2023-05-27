// Fill out your copyright notice in the Description page of Project Settings.


#include "PRocketLauncher.h"

APRocketLauncher::APRocketLauncher()
{
	SetGunshotSFX(GunshotPath);
}

void APRocketLauncher::BeginPlay()
{
	Super::BeginPlay();
	SetDamageAmount(100.0f);
}

void APRocketLauncher::PrimaryFire(APlayerController* PController, AActor* PossessedActor)
{
	PlayGunshotSFX(PossessedActor);
}