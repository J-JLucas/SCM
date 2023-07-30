// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableActor_Keycard.h"
#include "SCMarine/SCMPlayerCharacter.h"

void APickableActor_Keycard::BeginPlay()
{
	Super::BeginPlay();
}

void APickableActor_Keycard::PlayerPickedUp(ASCMPlayerCharacter* PlayerChar)
{
	if (KeyType == 0)
	{
		PlayerChar->GiveBlueKey();
		Super::PlayerPickedUp(PlayerChar);
		return;
	}

	if (KeyType == 1)
	{
		PlayerChar->GiveYellowKey();
		Super::PlayerPickedUp(PlayerChar);
		return;
	}
}
