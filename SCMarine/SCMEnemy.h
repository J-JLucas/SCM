// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Public/HealthInterface.h"
#include "SCMEnemy.generated.h"

UCLASS()
class SCMARINE_API ASCMEnemy : public ACharacter, public IHealthInterface
{
	GENERATED_BODY()

private:

public:
	// Sets default values for this character's properties
	ASCMEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Health 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthComponent")
	class UHealthComponent* HealthComponent;
	
	float DefaultHealth = 100.0f;

	virtual void OnDeath_Implementation() override;
		
	// Death Animation
	UPROPERTY()
	UAnimSequence* DeathAnimation;
	
	// Melee Attack Collision Boxes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackCollision")
	class UCapsuleComponent* AttackCollisionLeft = nullptr;

	// Melee Attack Collision Boxes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackCollision")
	class UCapsuleComponent* AttackCollisionRight = nullptr;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = Attack)
	virtual void MeleeAttack();

	// Skeletal Mesh Component
	//UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	//	USkeletalMeshComponent* EnemyMeshComponent;

	// Load the skeletal mesh asset
	//USkeletalMesh* EnemyMesh;


	void OnTakeDamage_Implementation();


};
