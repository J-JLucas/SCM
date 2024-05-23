//https://www.youtube.com/watch?v=1g1nhuy-kAI

#include "AI/BTTask_FindRandomLocation.h"
#include "NavigationSystem.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindRandomLocation::UBTTask_FindRandomLocation(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Find Random Location In NavMesh";
}

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// get AI controller and it's pawn
	if (AAIController* const AIController = OwnerComp.GetAIOwner())
	{
		if (AIController)
		{
			APawn* Pawn = AIController->GetPawn();
			if (Pawn)
			{
				// grab current location to set origin
				auto const Origin = Pawn->GetActorLocation();

				if (auto* const NavSys = UNavigationSystemV1::GetCurrent(GetWorld()))
				{
					FNavLocation Location;
					if (NavSys->GetRandomPointInNavigableRadius(Origin, SearchRadius, Location))
					{
						OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Location.Location);
						FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
						return EBTNodeResult::Succeeded;
					}
				}
			}
		}

	}
	return EBTNodeResult::Failed;
}
