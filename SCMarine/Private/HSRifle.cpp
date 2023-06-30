// Fill out your copyright notice in the Description page of Project Settings.


#include "HSRifle.h"

AHSRifle::AHSRifle()
	:Super()
{
	SetGunshotSFX(GunshotPath);
	SetImpactDecal(ImpactDecalPath);
	SetBloodEffect(BloodEffectPath);
	FireRate = 0.08f;
	ReloadRate = 2.4f;
	MaxAmmo = 600.0f;
	CurrentAmmo = 100.0f;
	MaxMag = 50;
	CurrentMag = 50;
	Name = FText::FromString("C-14 'IMPALER' RIFLE");
}


void AHSRifle::BeginPlay()
{
	Super::BeginPlay();
	SetDamageAmount(10.0f);
}
