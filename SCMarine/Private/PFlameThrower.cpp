// Fill out your copyright notice in the Description page of Project Settings.


#include "PFlameThrower.h"

APFlameThrower::APFlameThrower()
	:Super()
{
	// Find the blueprint class reference for ASCMProjectile
	static ConstructorHelpers::FObjectFinder<UClass> ProjectileBlueprint(TEXT("/Game/Blueprints/Guns/BP_FlamePrj.BP_FlamePrj_C"));
	// PATH format: TEXT("/Game/Blueprints/Guns/BP_SlimePrj.BP_SlimePrj_C")
	if (ProjectileBlueprint.Object)
	{
		SCMProjectileClass = ProjectileBlueprint.Object;
	}
	SetGunshotSFX(GunshotPath);
	FireRate = 0.2f;
	ReloadRate = 3.0f;
	MaxAmmo = 300.0f;
	CurrentAmmo = 0.0f;
	MaxMag = 75;
	CurrentMag = 75;
	Name = FText::FromString("C-140 'INCINERATOR'");
}

void APFlameThrower::BeginPlay()
{
	Super::BeginPlay();

}
