// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SCMWeapon.h"
#include "SCMProjectileWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SCMARINE_API ASCMProjectileWeapon : public ASCMWeapon
{
	GENERATED_BODY()
		
protected:

	// Spawns Projectile
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TestProjectile)
	TSubclassOf<class ASCMProjectile> SCMProjectileClass;

	// Projectile Blueprint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TestProjectile)
	UBlueprint* ProjClass;

	// Gun muzzle offset from camera location
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

public:
		
	void PrimaryFire() override;

};
