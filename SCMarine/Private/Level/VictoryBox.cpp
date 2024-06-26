// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/VictoryBox.h"
#include "Components/BoxComponent.h"
#include "SCMPlayerCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "SCMarinePlayerController.h"

// Sets default values
AVictoryBox::AVictoryBox()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = RootScene;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetBoxExtent(FVector(60.0f, 60.0f, 60.0f));
	CollisionBox->SetRelativeLocation(FVector(0.0f, 0.0f, 120.0f));
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AVictoryBox::OnBeginOverlap);

}

// Called when the game starts or when spawned
void AVictoryBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVictoryBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//void AVictoryBox::GoToNextLevel()
//{
		//UGameplayStatics::OpenLevelBySoftObjectPtr(this, NextLevel);
		//UGameplayStatics::OpenLevel(this, NextLevelFName);
//}



void AVictoryBox::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASCMPlayerCharacter* PlayerChar = Cast<ASCMPlayerCharacter>(OtherActor);
	if (PlayerChar)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Player Overlapped With VictoryBox!"));
		//ASCMarinePlayerController* PController = Cast<ASCMarinePlayerController>(PlayerChar->GetController());
		//if (PController)
	//	{
			//PController->ArmNextLevel();
		//}

	}
}


