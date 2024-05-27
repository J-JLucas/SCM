// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class SCMARINE_API UBTTask_MeleeAttack : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	explicit UBTTask_MeleeAttack(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};