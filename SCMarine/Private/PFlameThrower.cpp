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
}

void APFlameThrower::BeginPlay()
{
	Super::BeginPlay();

}
