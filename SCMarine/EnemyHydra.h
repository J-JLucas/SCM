// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SCMEnemy.h"
#include "EnemyHydra.generated.h"

/**
 * 
 */
UCLASS()
class SCMARINE_API AEnemyHydra : public ASCMEnemy
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

	UFUNCTION(BlueprintCallable, Category = Attack)
	void HydraRangedAttack(FRotator TargetAngle);
};
