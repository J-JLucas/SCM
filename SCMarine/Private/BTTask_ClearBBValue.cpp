// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ClearBBValue.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ClearBBValue::UBTTask_ClearBBValue(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Clear BlackBoard Value";
}

EBTNodeResult::Type UBTTask_ClearBBValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (BlackboardKey.SelectedKeyName.IsNone())
    {
        // No key selected, cannot clear
        return EBTNodeResult::Failed;
    }

    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (BlackboardComp)
    {
        // Clear the value at the specified key
        BlackboardComp->ClearValue(BlackboardKey.SelectedKeyName);

        // Successfully cleared the value
        return EBTNodeResult::Succeeded;
    }

    // Blackboard component not found or other failure
    return EBTNodeResult::Failed;
}
