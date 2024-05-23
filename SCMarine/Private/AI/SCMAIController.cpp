// Fill out your copyright notice in the Description page of Project Settings.
//https://www.youtube.com/watch?v=jzhbLFMcrPA&t=244s

#include "AI/SCMAIController.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Enemy/SCMEnemy.h"
#include "SCMPlayerCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Hearing.h"


ASCMAIController::ASCMAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
	SetupPerceptionSystem();
}

void ASCMAIController::BeginPlay()
{
	Super::BeginPlay();
}


void ASCMAIController::SetupPerceptionSystem()
{
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	if (SightConfig)
	{
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
		SightConfig->SightRadius = 5000.0f;
		SightConfig->LoseSightRadius = SightConfig->SightRadius + 500.0f;
		SightConfig->PeripheralVisionAngleDegrees = 50.0f;
		SightConfig->SetMaxAge(3.0f);
		SightConfig->AutoSuccessRangeFromLastSeenLocation = -1.0f;
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

		GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ASCMAIController::OnTargetDetected);
		GetPerceptionComponent()->ConfigureSense(*SightConfig);

		UE_LOG(LogTemp, Warning, TEXT("Perception Setup Successful!"));
	}

	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing Config"));
	if (HearingConfig)
	{
		HearingConfig->HearingRange = 3000.0f;
		HearingConfig->SetMaxAge(3.0f);
		HearingConfig->bUseLoSHearing = false;  // Depends on your game needs
		HearingConfig->LoSHearingRange = 1500.0f;
		HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
		HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;
		HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;
		GetPerceptionComponent()->ConfigureSense(*HearingConfig);
	}

}


void ASCMAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (ASCMEnemy* const AIPawn = Cast<ASCMEnemy>(InPawn))
	{
		if (UBehaviorTree* const BehaviorTree = AIPawn->GetBehaviorTree())
		{
			UBlackboardComponent* b;
			/*~ Wise man once said, take this extra step to avoid crashes */
			// tries to get the blackboard asset
			// if one exists, it puts it in the 'b' struct
			// if it DOESN"T exist, creates one and places it in 'b'
			UseBlackboard(BehaviorTree->BlackboardAsset, b);
			Blackboard = b;
			RunBehaviorTree(BehaviorTree);
		}
	}
}

void ASCMAIController::OnUnPossess()
{
	Super::OnUnPossess();
	Destroy();
}

// Handles Perception Events
// Determines sense type and calls 
// corresponding handler
void ASCMAIController::OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus)
{
	UE_LOG(LogTemp, Warning, TEXT("Stimulus Detected!"));

	if (!Stimulus.IsValid() || !((Stimulus.Type).IsValid()) )
	{
		UE_LOG(LogTemp, Warning, TEXT("Abort Sense Update, invalid stimulus"));
	}

	ASCMPlayerCharacter* PlayerChar = Cast<ASCMPlayerCharacter>(Actor);
	if (PlayerChar)
	{
		if (SightConfig && Stimulus.Type == SightConfig->GetSenseID())
		{
			// Handle sight
			HandleSightUpdate(PlayerChar, Stimulus);
		}
		else if (HearingConfig && Stimulus.Type == HearingConfig->GetSenseID())
		{
			// Handle hearing
			HandleHearingUpdate(PlayerChar, Stimulus);
		}
	}
}


void ASCMAIController::HandleSightUpdate(ASCMPlayerCharacter* PlayerChar, FAIStimulus const Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		// Set the player character as the target on the blackboard
		GetBlackboardComponent()->SetValueAsObject(FName("Target Actor"), PlayerChar);

		// Play Alert Bark
		ASCMEnemy* const AIPawn = Cast<ASCMEnemy>(GetPawn());
		if (AIPawn && bPlaySpottedAlert)
		{
			AIPawn->PlayAlertBark();
		}
		UE_LOG(LogTemp, Warning, TEXT("Target spotted!"));
	}
	else
	{
		// Update signifies lost sight of player
		// Clear target value on the blackboard and set last known location
		GetBlackboardComponent()->SetValueAsObject(FName("Target Actor"), nullptr);
		GetBlackboardComponent()->SetValueAsVector(FName("Last Known Location"), PlayerChar->GetActorLocation());
		bPlaySpottedAlert = true;
	}
}


void ASCMAIController::HandleHearingUpdate(ASCMPlayerCharacter* PlayerChar, FAIStimulus const Stimulus)
{
	GetBlackboardComponent()->SetValueAsVector("Target Location", Stimulus.StimulusLocation);
}


// Disable perception when a enemy pawn dies
void ASCMAIController::DeactivatePerception()
{
	//GetPerceptionComponent()->Deactivate();
	GetBlackboardComponent()->SetValueAsBool(FName("IsDead"), true);
	GetPerceptionComponent()->DestroyComponent();
	UnPossess();
}
