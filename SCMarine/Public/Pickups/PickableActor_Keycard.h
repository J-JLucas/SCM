// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickableActor_Base.h"
#include "PickableActor_Keycard.generated.h"

UENUM(BlueprintType)
enum KeyType
{
	NoKey UMETA(DisplayName = "NoKey"),	
	BlueKey UMETA(DisplayName = "BlueKey"),
	PurpleKey UMETA(DisplayName = "PurpleKey"),
	YellowKey UMETA(DisplayName = "YellowKey"),

};

UCLASS()
class SCMARINE_API APickableActor_Keycard : public APickableActor_Base
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
	virtual void PlayerPickedUp(class ASCMPlayerCharacter* PlayerChar)override;

public:

	UPROPERTY(EditAnywhere, Category = KeyCollectable)
	TEnumAsByte<KeyType> Key;

};
