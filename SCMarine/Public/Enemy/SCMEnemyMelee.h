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

private:
	UAnimMontage* ChooseAttackMontage();

protected:

	// Melee Attack Collision Boxes
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackCollision")
	//class UCapsuleComponent* AttackCollisionLeft = nullptr;

	// Melee Attack Collision Boxes
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackCollision")
	//class UCapsuleComponent* AttackCollisionRight = nullptr;

	// Array of animation montages
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TArray<UAnimMontage*> AttackMontages;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound")
	class USoundBase* MeleeAttackSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	float MeleeAttackDamage{10};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	float MeleeForce{ -250.0f };  // This is how my bp was set up, don't remember why negative lol

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	float ForceHeight{ 50.0f };

	UFUNCTION(BlueprintCallable, Category = "Attack")
	virtual void MeleeAttack();

	UFUNCTION(BlueprintCallable, Category = "Attack")
	virtual void DealMeleeDamage(AActor* Target, UPrimitiveComponent* MeleeHitbox);

};
