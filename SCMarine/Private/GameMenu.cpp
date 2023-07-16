// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "SCMarine/SCMarinePlayerController.h"



/*
UGameMenu::UGameMenu(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	
}
*/


void UGameMenu::OnPauseClicked()
// Pause Gameplay
{
	ASCMarinePlayerController* PlayerController = Cast<ASCMarinePlayerController>(GetOwningPlayer());
	if (PlayerController)
	{
		if (PlayerController->IsPaused())
		{
			PlayerController->SetPause(false);
		}
		else
		{
			PlayerController->SetPause(true);
		}
	}
}

void UGameMenu::OnControlsClicked()
// Controller binds info eventually
{
	return;
}

void UGameMenu::OnRestartClicked()
{
	ASCMarinePlayerController* PlayerController = Cast<ASCMarinePlayerController>(GetOwningPlayer());
	if (PlayerController)
	{
		PlayerController->HideGameMenu();
	}
	UGameplayStatics::OpenLevel(this, FName(*UGameplayStatics::GetCurrentLevelName(this)));
}

void UGameMenu::OnExitClicked()
// Exit Game
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, true);
}

void UGameMenu::OnReturnClicked()
// Return to Gameplay
{
	ASCMarinePlayerController* PlayerController = Cast<ASCMarinePlayerController>(GetOwningPlayer());
	if (PlayerController)
	{
		//PlayerController->SetInputMode(FInputModeGameOnly());
		//PlayerController->GetPawn()->EnableInput(PlayerController);
		//PlayerController->bShowMouseCursor = false;
		PlayerController->HideGameMenu();
	}
}

void UGameMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();


	// Bind all the functions to the button clicks
	if (PauseButton)
	{
		PauseButton->OnClicked.AddDynamic(this, &UGameMenu::OnPauseClicked);
	}

	if (ControlsButton)
	{
		ControlsButton->OnClicked.AddDynamic(this, &UGameMenu::OnControlsClicked);
	}

	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UGameMenu::OnRestartClicked);
	}

	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &UGameMenu::OnExitClicked);
	}

	if (ReturnButton)
	{
		ReturnButton->OnClicked.AddDynamic(this, &UGameMenu::OnReturnClicked);
	}
}