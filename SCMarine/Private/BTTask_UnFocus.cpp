#include "BTTask_UnFocus.h"
#include "AIController.h"

UBTTask_UnFocus::UBTTask_UnFocus(const FObjectInitializer& ObjectInitializer)
{
    NodeName = "Unfocus from Target";
}

EBTNodeResult::Type UBTTask_UnFocus::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController)
    {
        return EBTNodeResult::Failed;
    }

    AIController->ClearFocus(EAIFocusPriority::Gameplay);
    return EBTNodeResult::Succeeded;
}