// Fill out your copyright notice in the Description page of Project Settings.


#include "HSSniper.h"

AHSSniper::AHSSniper()
	:Super()
{
	SetGunshotSFX(GunshotPath);

}

void AHSSniper::BeginPlay()
{
	Super::BeginPlay();
	SetDamageAmount(100.0f);
}
