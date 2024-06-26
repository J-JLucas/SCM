// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SCMEnemyMelee.h"
#include "SCMEnemyRanged.generated.h"

/**
 * 
 */
UCLASS()
class SCMARINE_API ASCMEnemyRanged : public ASCMEnemyMelee
{
	GENERATED_BODY()

protected:
	// Array of animation montages
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TArray<UAnimMontage*> RangedAttackMontages;

	//FTimerHandle RangedAttackTimer;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	//float RangedAttackRate{ 1.0f };

public:
	UFUNCTION(BlueprintCallable, Category = "Attack")
	virtual void RangedAttack();
};
