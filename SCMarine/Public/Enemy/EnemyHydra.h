// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SCMEnemyRanged.h"
#include "EnemyHydra.generated.h"

/**
 * 
 */
UCLASS()
class SCMARINE_API AEnemyHydra : public ASCMEnemyRanged
{
	GENERATED_BODY()

protected:

	// Spawns Projectile
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TestProjectile)
	TSubclassOf<class ASCMProjectile> SCMProjectileClass;

	// Projectile Blueprint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TestProjectile)
	UBlueprint* ProjClass;

public:

	AEnemyHydra();

	virtual void RangedAttack() override;
};
