// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/PickableActor_HealthPickup.h"
#include "SCMPlayerCharacter.h"


void APickableActor_HealthPickup::BeginPlay()
{
	Super::BeginPlay();
}

void APickableActor_HealthPickup::PlayerPickedUp(ASCMPlayerCharacter* PlayerChar)
{
	bool Success = PlayerChar->HealPlayer(HealthAmount);
	if (Success)
	{
		Super::PlayerPickedUp(PlayerChar);
	}
}
