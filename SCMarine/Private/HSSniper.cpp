// Fill out your copyright notice in the Description page of Project Settings.


#include "HSSniper.h"

AHSSniper::AHSSniper()
	:Super()
{
	SetGunshotSFX(GunshotPath);
	SetImpactDecal(ImpactDecalPath);
	SetBloodEffect(BloodEffectPath);
	FireRate = 1.5;
	ReloadRate = 3.7f;
	MaxAmmo = 50.0f;
	CurrentAmmo = 10.0f;
	MaxMag = 5;
	CurrentMag = 5;
	Name = FText::FromString("HEV 'COMMANDO' RIFLE");
}

void AHSSniper::BeginPlay()
{
	Super::BeginPlay();
	SetDamageAmount(100.0f);
}
