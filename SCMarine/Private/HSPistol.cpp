// Fill out your copyright notice in the Description page of Project Settings.


#include "HSPistol.h"

AHSPistol::AHSPistol()
	:Super()
{
	SetGunshotSFX(GunshotPath);
	FireRate = 0.25f;
	ReloadRate = 2.2f;
	MaxAmmo = 50.0f;
	CurrentAmmo = 0.0f;
	MaxMag = 7;
	CurrentMag = 7;
	Name = FText::FromString(".50 'MAR SARA SPECIAL'");
}

void AHSPistol::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// Call BeginPlay here
	BeginPlay();
}

void AHSPistol::BeginPlay()
{
	Super::BeginPlay();
	SetDamageAmount(10.0f);
}