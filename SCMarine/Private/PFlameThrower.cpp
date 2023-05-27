// Fill out your copyright notice in the Description page of Project Settings.


#include "PFlameThrower.h"

APFlameThrower::APFlameThrower()
{
	SetGunshotSFX(GunshotPath);
}

void APFlameThrower::BeginPlay()
{
	Super::BeginPlay();
	SetDamageAmount(50.0f);
}

void APFlameThrower::PrimaryFire(APlayerController* PController, AActor* PossessedActor)
{
	PlayGunshotSFX(PossessedActor);
}
