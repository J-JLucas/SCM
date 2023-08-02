// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableActor_Keycard.h"
#include "SCMarine/SCMPlayerCharacter.h"

void APickableActor_Keycard::BeginPlay()
{
	Super::BeginPlay();
}

void APickableActor_Keycard::PlayerPickedUp(ASCMPlayerCharacter* PlayerChar)
{
		PlayerChar->GiveKey(Key);
		Super::PlayerPickedUp(PlayerChar);
		
		return;
}
