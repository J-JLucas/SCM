// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_RangedAttack.generated.h"

/**
 * 
 */
UCLASS()
class SCMARINE_API UBTTask_RangedAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	explicit UBTTask_RangedAttack(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};