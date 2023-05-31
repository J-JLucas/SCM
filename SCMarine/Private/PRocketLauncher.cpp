// Fill out your copyright notice in the Description page of Project Settings.


#include "PRocketLauncher.h"

APRocketLauncher::APRocketLauncher()
	:Super()
{
	// Find the blueprint class reference for ASCMProjectile
	static ConstructorHelpers::FObjectFinder<UClass> ProjectileBlueprint(TEXT("/Game/Blueprints/Guns/BP_RocketPrj.BP_RocketPrj_C"));
	if (ProjectileBlueprint.Object)
	{
		SCMProjectileClass = ProjectileBlueprint.Object;
	}
	
	SetGunshotSFX(GunshotPath);
}

void APRocketLauncher::BeginPlay()
{
	Super::BeginPlay();
}