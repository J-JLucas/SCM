#include "AI/BTTask_Focus.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

UBTTask_Focus::UBTTask_Focus(const FObjectInitializer& ObjectInitializer)
{
    NodeName = "Focus on Target";
}

EBTNodeResult::Type UBTTask_Focus::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController)
    {
        return EBTNodeResult::Failed;
    }

    ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (!PlayerCharacter)
    {
        return EBTNodeResult::Failed;
    }

    AIController->SetFocus(PlayerCharacter);
    return EBTNodeResult::Succeeded;
}