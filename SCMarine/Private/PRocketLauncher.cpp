// Fill out your copyright notice in the Description page of Project Settings.


#include "PRocketLauncher.h"

APRocketLauncher::APRocketLauncher()
	:Super()
{
	// Find the blueprint class reference for ASCMProjectile
	//static ConstructorHelpers::FObjectFinder<UClass> ProjectileBlueprint(TEXT("/Game/Blueprints/Guns/BP_RocketPrj.BP_RocketPrj_C"));
	static ConstructorHelpers::FObjectFinder<UClass> ProjectileBlueprint(TEXT("/Game/Blueprints/Guns/BP_BloodProjectile.BP_BloodProjectile_C"));
	if (ProjectileBlueprint.Object)
	{
		SCMProjectileClass = ProjectileBlueprint.Object;
	}
	
	SetGunshotSFX(GunshotPath);
	FireRate = 0.9;
	ReloadRate = 3.5f;
	MaxAmmo = 50.0f;
	CurrentAmmo = 0.0f;
	MaxMag = 5;
	CurrentMag = 5;
	Name = FText::FromString("K-12 'PUNISHER' RPG");
}

void APRocketLauncher::BeginPlay()
{
	Super::BeginPlay();
}