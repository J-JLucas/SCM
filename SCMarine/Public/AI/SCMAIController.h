// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SCMAIController.generated.h"

/**
 * 
 */
UCLASS()
class SCMARINE_API ASCMAIController : public AAIController
{
	GENERATED_BODY()

public:
	explicit ASCMAIController(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

protected:

	//class UAISenseConfig_Sight* SightConfig;
	//class UAISenseConfig_Hearing* HearingConfig;
	bool bPlaySpottedAlert{true};

	//virtual void OnPossess(APawn* InPawn) override;
	//virtual void OnUnPossess() override;
	//void SetupPerceptionSystem();
	
	//UFUNCTION()
	//void OnTargetDetected(AActor* Actor, struct FAIStimulus const Stimulus);

	UFUNCTION(BlueprintCallable)
	void HandleSightUpdate(AActor* SensedActor, struct FAIStimulus const Stimulus);
	UFUNCTION(BlueprintCallable)
	void HandleHearingUpdate(AActor* SensedActor, struct FAIStimulus const Stimulus);
	//UFUNCTION(BlueprintCallable)
	//void HandleTakeDamage();

public:
	//void DeactivatePerception();
};
