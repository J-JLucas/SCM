// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableActor_WeaponPickup.h"
#include "SCMarine/SCMPlayerCharacter.h"

void APickableActor_WeaponPickup::BeginPlay()
{
	Super::BeginPlay();
}

void APickableActor_WeaponPickup::PlayerPickedUp(ASCMPlayerCharacter* PlayerChar)
{
	bool Success = PlayerChar->PickupWeapon(GunType, AmmoAmount);

	if(Success)
	{
		Super::PlayerPickedUp(PlayerChar);
	}
}
