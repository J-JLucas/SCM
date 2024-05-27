// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_RangedAttack.h"
#include "AIController.h"
#include "Enemy/SCMEnemyRanged.h"


UBTTask_RangedAttack::UBTTask_RangedAttack(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Execute Ranged Attack";
}

EBTNodeResult::Type UBTTask_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	{
		// get AI controller and it's pawn
		if (AAIController* const AIController = OwnerComp.GetAIOwner())
		{
			if (AIController)
			{
				ASCMEnemyRanged* Pawn = Cast<ASCMEnemyRanged>(AIController->GetPawn());
				if (Pawn)
				{
					Pawn->RangedAttack();
					return EBTNodeResult::Succeeded;
				}
			}
		}
		return EBTNodeResult::Failed;
	}
}
