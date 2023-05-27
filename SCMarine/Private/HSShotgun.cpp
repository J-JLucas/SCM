// Fill out your copyright notice in the Description page of Project Settings.


#include "HSShotgun.h"

AHSShotgun::AHSShotgun()
{
	SetGunshotSFX(GunshotPath);
	
}

void AHSShotgun::BeginPlay()
{
	Super::BeginPlay();
	SetDamageAmount(50.0f);
}