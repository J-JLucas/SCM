// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SCMarine/SCMEnemy.h"
#include "EnemyInfestedMarine.generated.h"

/**
 * 
 */
UCLASS()
class SCMARINE_API AEnemyInfestedMarine : public ASCMEnemy
{
	GENERATED_BODY()
	

public:
	
	AEnemyInfestedMarine();

	UFUNCTION(BlueprintCallable, Category = Attack)
	void IMRangedAttack();
};
