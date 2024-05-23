// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/PickableActor_Stimpack.h"
#include "SCMPlayerCharacter.h"

void APickableActor_Stimpack::PlayerPickedUp(ASCMPlayerCharacter* PlayerChar)
{
	PlayerChar->ActivateStim();
	Super::PlayerPickedUp(PlayerChar);

	return;
}