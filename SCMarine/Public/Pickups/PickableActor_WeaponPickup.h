// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickableActor_Base.h"
//#include "SCMWeapon.h"
#include "PickableActor_WeaponPickup.generated.h"

/**
 * 
 */
UCLASS()
class SCMARINE_API APickableActor_WeaponPickup : public APickableActor_Base
{
	GENERATED_BODY()
protected:

	virtual void BeginPlay() override;
	virtual void PlayerPickedUp(class ASCMPlayerCharacter* PlayerChar)override;

public:

	UPROPERTY(EditAnywhere, Category = WeaponCollectable)
	TEnumAsByte<enum WeaponType> GunType;

	UPROPERTY(EditAnywhere, Category = WeaponCollectable)
	int AmmoAmount{ 10 };
};
