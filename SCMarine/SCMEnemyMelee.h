// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SCMEnemy.h"
#include "SCMEnemyMelee.generated.h"

/**
 * 
 */
UCLASS()
class SCMARINE_API ASCMEnemyMelee : public ASCMEnemy
{
	GENERATED_BODY()
	
public:
	ASCMEnemyMelee();

protected:

	// Melee Attack Collision Boxes
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackCollision")
	//class UCapsuleComponent* AttackCollisionLeft = nullptr;

	// Melee Attack Collision Boxes
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackCollision")
	//class UCapsuleComponent* AttackCollisionRight = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound")
	class USoundBase* MeleeAttackSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	float MeleeAttackDamage{10};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	float MeleeForce{ -250.0f };

	UFUNCTION(BlueprintCallable, Category = Attack)
	virtual void MeleeAttack(AActor* Target, UPrimitiveComponent* MeleeHitbox);

};
