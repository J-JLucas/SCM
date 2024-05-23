// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickableActor_Base.h"
#include "PickableActor_Stimpack.generated.h"

/**
 * 
 */
UCLASS()
class SCMARINE_API APickableActor_Stimpack : public APickableActor_Base
{
	GENERATED_BODY()
	
protected:

	virtual void PlayerPickedUp(class ASCMPlayerCharacter* PlayerChar)override;
};
