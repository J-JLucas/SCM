// Fill out your copyright notice in the Description page of Project Settings.


#include "HSPistol.h"

AHSPistol::AHSPistol()
	:Super()
{
	SetGunshotSFX(GunshotPath);
}

void AHSPistol::BeginPlay()
{
	Super::BeginPlay();
	SetDamageAmount(10.0f);
}