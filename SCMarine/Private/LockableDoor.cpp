// Fill out your copyright notice in the Description page of Project Settings.


#include "LockableDoor.h"
#include "Engine/SkeletalMesh.h"
#include "Components/BoxComponent.h"
#include "SCMarine/SCMPlayerCharacter.h"
#include "PickableActor_Keycard.h"
#include "TimerManager.h"

// Sets default values
ALockableDoor::ALockableDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DoorMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("DoorMesh"));
	check(DoorMesh != nullptr);
	DoorMesh->SetupAttachment(RootComponent);

	ActivationBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ActivationCollision"));
	ActivationBox->InitBoxExtent(FVector(200.0f, 300.0f, 128.0f));
	ActivationBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	ActivationBox->SetupAttachment(DoorMesh);

	LeftCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftBoxCollision"));
	LeftCollisionBox->InitBoxExtent(FVector(1.0f, 1.0f, 1.0f));
	LeftCollisionBox->SetCollisionProfileName(TEXT("BlockAll"));
	LeftCollisionBox->SetupAttachment(DoorMesh, TEXT("LeftDoorCollision"));

	RightCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RightBoxCollision"));
	RightCollisionBox->InitBoxExtent(FVector(1.0f, 1.0f, 1.0f));
	RightCollisionBox->SetCollisionProfileName(TEXT("BlockAll"));
	RightCollisionBox->SetupAttachment(DoorMesh, TEXT("RightDoorCollision"));
}

// Called when the game starts or when spawned
void ALockableDoor::BeginPlay()
{
	Super::BeginPlay();
	
	ActivationBox->OnComponentBeginOverlap.AddDynamic(this, &ALockableDoor::BeginOverlap);
	ActivationBox->OnComponentEndOverlap.AddDynamic(this, &ALockableDoor::EndOverlap);

	if (LockType == NoKey)
	{
		bIsLocked = false;
	}
}

void ALockableDoor::StartDoorTimer()
{
	GetWorldTimerManager().SetTimer(DoorTimerHandle, this, &ALockableDoor::StopDoorTimer, DoorTimerLength, false);
}

void ALockableDoor::StopDoorTimer()
{
	GetWorldTimerManager().ClearTimer(DoorTimerHandle);
	bDoorIsOpen = false;

}

void ALockableDoor::BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASCMPlayerCharacter* PlayerChar = Cast<ASCMPlayerCharacter>(OtherActor);
	if (PlayerChar)
	{
		if (bIsLocked)
		{
			if (PlayerChar->CheckHasKey(LockType))
			{
				bIsLocked = false;
			}
			else
			{
				return;
			}
		}
		GetWorldTimerManager().ClearTimer(DoorTimerHandle);
		bDoorIsOpen = true;
		return;
	}
}

void ALockableDoor::EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (bIsLocked) { return; }

	ASCMPlayerCharacter* PlayerChar = Cast<ASCMPlayerCharacter>(OtherActor);
	if (PlayerChar)
	{
		StartDoorTimer();
	}
}


