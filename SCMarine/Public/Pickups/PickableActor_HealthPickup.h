// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickableActor_Base.h"
#include "PickableActor_HealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class SCMARINE_API APickableActor_HealthPickup : public APickableActor_Base
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;
	virtual void PlayerPickedUp(class ASCMPlayerCharacter* PlayerChar)override;

public:
	UPROPERTY(EditAnywhere, Category = HealthCollectable)
	float HealthAmount{20};

};
