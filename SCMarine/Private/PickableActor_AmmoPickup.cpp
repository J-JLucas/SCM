// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableActor_AmmoPickup.h"
#include "SCMarine/SCMPlayerCharacter.h"

void APickableActor_AmmoPickup::BeginPlay()
{
	Super::BeginPlay();
}

void APickableActor_AmmoPickup::PlayerPickedUp(ASCMPlayerCharacter* PlayerChar)
{
	bool Success = PlayerChar->PickupAmmo(AmmoType, AmmoAmount);
	if (Success)
	{
		Super::PlayerPickedUp(PlayerChar);
	}
}

