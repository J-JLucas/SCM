// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
//#include "Components/Slider.h"
//#include "Components/EditableText.h"
#include "SCMarinePlayerController.h"

/*
UGameMenu::UGameMenu(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	
}
*/

void UGameMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();


	// Bind all the functions to the button clicks
	// Apparently you can't pass arguments so had to hardcode
	// for going back each parent menu
	if (SaveButton)
	{
		SaveButton->OnClicked.AddDynamic(this, &UGameMenu::OnSavedClicked);
	}

	if (LoadButton)
	{
		LoadButton->OnClicked.AddDynamic(this, &UGameMenu::OnLoadClicked);
	}

	if (OptionsButton)
	{
		OptionsButton->OnClicked.AddDynamic(this, &UGameMenu::OnOptionsClicked);
	}
	
	if (OptionsBackButton)
	{
		OptionsBackButton->OnClicked.AddDynamic(this, &UGameMenu::OnBackMainClicked);
	}

	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UGameMenu::OnRestartClicked);
	}

	if (QuitToMenuButton)
	{
		QuitToMenuButton->OnClicked.AddDynamic(this, &UGameMenu::OnQuitToMenuClicked);
	}

	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &UGameMenu::OnExitClicked);
	}

	if (ReturnButton)
	{
		ReturnButton->OnClicked.AddDynamic(this, &UGameMenu::OnReturnClicked);
	}

	if (InputButton)
	{
		InputButton->OnClicked.AddDynamic(this, &UGameMenu::OnInputClicked);
	}

	if (InputBackButton)
	{
		InputBackButton->OnClicked.AddDynamic(this, &UGameMenu::OnBackOptionsClicked);
	}

	if (SoundButton)
	{
		SoundButton->OnClicked.AddDynamic(this, &UGameMenu::OnSoundClicked);
	}

	if (SoundBackButton)
	{
		SoundBackButton->OnClicked.AddDynamic(this, &UGameMenu::OnBackOptionsClicked);
	}

	if (DisplayButton)
	{
		DisplayButton->OnClicked.AddDynamic(this, &UGameMenu::OnDisplayClicked);
	}

	if (DisplayBackButton)
	{
		DisplayBackButton->OnClicked.AddDynamic(this, &UGameMenu::OnBackOptionsClicked);
	}

	return;
}

/*
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
*/

void UGameMenu::OnSavedClicked()
{
	return;
}

void UGameMenu::OnLoadClicked()
{
	return;
}
void UGameMenu::OnOptionsClicked()
{
	SwitchCanvas(OptionsMenu);
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
	return;
}

void UGameMenu::OnQuitToMenuClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("99MainMenu"));
	return;
}

void UGameMenu::OnExitClicked()
// Exit Game
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, true);
	return;
}

void UGameMenu::OnInputClicked()
{
	SwitchCanvas(InputMenu);
	return;
}

void UGameMenu::OnSoundClicked()
{
	SwitchCanvas(SoundMenu);
	return;
}

void UGameMenu::OnDisplayClicked()
{
	SwitchCanvas(DisplayMenu);
	return;
}

void UGameMenu::OnBackMainClicked()
{
	SwitchCanvas(BaseMenu);
	return;
}

void UGameMenu::OnBackOptionsClicked()
{
	SwitchCanvas(OptionsMenu);
	return;
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
	return;
}

void UGameMenu::SwitchCanvas(int32 CanvasIndex)
{
	//PreviousMenu = CurrentMenu;
	//CurrentMenu = CanvasIndex;
	DaWidgetSwitcher->SetActiveWidgetIndex(CanvasIndex);
	return;
}