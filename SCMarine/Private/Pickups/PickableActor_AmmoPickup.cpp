// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/PickableActor_AmmoPickup.h"
#include "SCMPlayerCharacter.h"
#include "Weapons/SCMWeapon.h"

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

