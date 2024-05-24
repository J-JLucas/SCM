// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HealthInterface.h"
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

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
	//USkeletalMeshComponent* CharacterMesh;

	// Health 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthComponent")
	class UHealthComponent* HealthComponent;
	
	float DefaultHealth{ 100.0f };

	virtual void OnDeath_Implementation() override;
	virtual void OnTakeDamage_Implementation() override;
		
	UPROPERTY(BlueprintReadWrite, Category = "Damage")
	bool bCanDealDamage{ false };

	// Flipped when enemy detects player
	UPROPERTY(BlueprintReadWrite, Category = "AI")
	bool bPlayerDetected = false;

	// Flipped when enemy spots player
	UPROPERTY(BlueprintReadWrite, Category = "AI")
	bool bPlayerVisable = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	class UBehaviorTree* BehaviorTree;

	FVector GetPlayerLocation() const;
	FRotator FindLookAtRotation(const FVector& Start, const FVector& Target);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadWrite, Category = "AI")
	FVector SpawnOrigin;

	UPROPERTY(EditDefaultsOnly)
	float MaxSpeed{100.0f};

	UPROPERTY(EditDefaultsOnly)
	float IdleSpeed{ 100.0f };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound")
	class USoundBase* AlertSound;

	void PlayAlertBark();

	UFUNCTION(BlueprintCallable)
	void SwitchToAttackSpeed();
	
	UFUNCTION(BlueprintCallable)
	void SwitchToWalkSpeed();

	FORCEINLINE UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }

};
