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

	// FPS mesh (arms); visible only to owning player
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
	//USkeletalMeshComponent* CharacterMesh;

	// Pawnsense
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	//class UPawnSensingComponent* PawnSenseComp;

	// Health 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthComponent")
	class UHealthComponent* HealthComponent;
	
	float DefaultHealth{ 100.0f };

	virtual void OnDeath_Implementation() override;
	virtual void OnTakeDamage_Implementation() override;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	bool bCanDealDamage{ false };

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

	UPROPERTY(BlueprintReadWrite, Category = "AISense")
	FVector SpawnOrigin;

	UPROPERTY(EditAnywhere)
	float MaxSpeed{100.0f};

	UPROPERTY(EditAnywhere)
	float IdleSpeed{ 100.0f };

	UFUNCTION(BlueprintCallable)
	void SwitchToAttackSpeed();
	
	UFUNCTION(BlueprintCallable)
	void SwitchToWalkSpeed();

};
