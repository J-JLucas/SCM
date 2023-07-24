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

	// Pawnsense
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	//class UPawnSensingComponent* PawnSenseComp;

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
	
	// Flipped when enemy detects player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AISense")
	bool bPlayerDetected = false;

	// Flipped when enemy spots player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AISense")
	bool bPlayerVisable = false;

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

	UPROPERTY(EditAnywhere)
	float MaxSpeed{100.0f};

	UPROPERTY(EditAnywhere)
	float IdleSpeed{ 100.0f };

	UFUNCTION(BlueprintCallable)
	void SwitchToAttackSpeed();
	
	UFUNCTION(BlueprintCallable)
	void SwitchToWalkSpeed();

	// Removed due to horrible performance,
	// Decals are bad, need to learn about 
	// RVT (runtime virtual texture) or render target capture to "paint" directly to the texture of a model 
	//UFUNCTION(BlueprintImplementableEvent, Category = GFX)
	//void SpawnBloodEffectEvent(FVector HitLocation, FVector HitNormal);

};
