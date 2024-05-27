// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_MeleeAttack.h"
#include "AIController.h"
#include "Enemy/SCMEnemyMelee.h"

UBTTask_MeleeAttack::UBTTask_MeleeAttack(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Execute Melee Attack";
}

EBTNodeResult::Type UBTTask_MeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// get AI controller and it's pawn
	if (AAIController* const AIController = OwnerComp.GetAIOwner())
	{
		if (AIController)
		{
			ASCMEnemyMelee* Pawn = Cast<ASCMEnemyMelee>(AIController->GetPawn());
			if (Pawn)
			{
				Pawn->MeleeAttack();
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
