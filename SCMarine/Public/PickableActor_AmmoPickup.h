// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickableActor_Base.h"
#include "PickableActor_AmmoPickup.generated.h"

/**
 * 
 */
UCLASS()
class SCMARINE_API APickableActor_AmmoPickup : public APickableActor_Base
{
	GENERATED_BODY()
protected:

	virtual void BeginPlay() override;
	virtual void PlayerPickedUp(class ASCMPlayerCharacter* PlayerChar)override;

public:

	UPROPERTY(EditAnywhere, Category = AmmoCollectable)
	int32 AmmoType{ 3 };

	UPROPERTY(EditAnywhere, Category = AmmoCollectable)
	float AmmoAmount{20};

};
