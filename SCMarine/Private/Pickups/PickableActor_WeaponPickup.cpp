// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/PickableActor_WeaponPickup.h"
#include "SCMPlayerCharacter.h"
#include "Weapons/SCMWeapon.h"

void APickableActor_WeaponPickup::BeginPlay()
{
	Super::BeginPlay();
}

void APickableActor_WeaponPickup::PlayerPickedUp(ASCMPlayerCharacter* PlayerChar)
{
	//bool Success = PlayerChar->PickupWeapon(GunType, AmmoAmount);
	bool HasGun = PlayerChar->PickupWeapon(GunType, AmmoAmount);

	bool Success = PlayerChar->PickupAmmo(GunType, AmmoAmount);

	if(!HasGun || Success)
	// Destory pickup if player didn't previously own gun
	// or if player is not maxed on ammo
	{
		Super::PlayerPickedUp(PlayerChar);
	}
}
