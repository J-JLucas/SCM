// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_Focus.generated.h"

/**
 * 
 */
UCLASS()
class SCMARINE_API UBTTask_Focus : public UBTTaskNode
{
	GENERATED_BODY()

public:
	explicit UBTTask_Focus(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};