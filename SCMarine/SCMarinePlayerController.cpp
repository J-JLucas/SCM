// Fill out your copyright notice in the Description page of Project Settings.


#include "SCMarinePlayerController.h"
#include "GameMenu.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputCoreTypes.h"
#include "HealthComponent.h"
#include "Public/HUDWidget.h"
#include "Kismet/GameplayStatics.h"

void ASCMarinePlayerController::BeginPlay()
{
	Super::BeginPlay();

    // Get the Enhanced Input subsystem
    UEnhancedInputLocalPlayerSubsystem* Subsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

    if (Subsystem)
    {
        // Add the mapping context
        Subsystem->AddMappingContext(IC_PlayerChar, 1);
        UE_LOG(LogTemp, Error, TEXT("Got Enhanced Input subsystem"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to get Enhanced Input subsystem"));
    }

    if (BP_PlayerHUD)
    {
        HUDWidget = CreateWidget<UHUDWidget>(this, BP_PlayerHUD);
        HUDWidget->AddToViewport();
    }

}

void ASCMarinePlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    // Get EnhancedInputComponent & Bind Actions
    UEnhancedInputComponent* EnhancedInputComponent = FindComponentByClass<UEnhancedInputComponent>();
    if (EnhancedInputComponent)
    {
        EnhancedInputComponent->BindAction(IA_GameMenu, ETriggerEvent::Triggered, this, &ASCMarinePlayerController::ShowGameMenu);

        if (InputComponent == nullptr)
        {
            UE_LOG(LogTemp, Warning, TEXT("Bind Action Null"));
        }
    }
}

void ASCMarinePlayerController::ShowGameMenu()
{
    UE_LOG(LogTemp, Warning, TEXT("Menu input received!"));
    if (BP_GameMenu)
    {

        if (GameMenu) 
        { 

            HideGameMenu();
            UE_LOG(LogTemp, Error, TEXT("Game Menu Already Exists, exit menu."));
            return;

        }

        if (!GameMenu)
        {
            GameMenu = CreateWidget<UGameMenu>(this, BP_GameMenu);
            if (GameMenu)
            {
                GameMenu->AddToViewport();
                GetPawn()->DisableInput(this);
                SetInputMode(FInputModeGameAndUI());
                bShowMouseCursor = true;
                UE_LOG(LogTemp, Warning, TEXT("Game Menu created and added to viewport."));
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to create Game Menu."));
            }
        }
    }
}

void ASCMarinePlayerController::HideGameMenu()
{
    UE_LOG(LogTemp, Error, TEXT("Hiding Game Menu."));
	GameMenu->RemoveFromParent();	// "unDraw"
	GameMenu->Destruct();			// kill
    GetPawn()->EnableInput(this);
    SetInputMode(FInputModeGameOnly());
    bShowMouseCursor = false;
	GameMenu = nullptr;

}

void ASCMarinePlayerController::UpdateHealthPercent(float HealthPercent)
{
    if (HUDWidget)
    {
        HUDWidget->UpdateHealthPercent(HealthPercent);
    }
}

void ASCMarinePlayerController::UpdateActiveWeaponName(FText Name)
{
    if (HUDWidget)
    {
        HUDWidget->UpdateWeaponText(Name);
    }
}

void ASCMarinePlayerController::UpdateMagCount(float Count)
{
    if (HUDWidget)
    {
        HUDWidget->UpdateMagazine(Count);
    }
}

void ASCMarinePlayerController::UpdateAmmoCount(float Count)
{
    if (HUDWidget)
    {
        HUDWidget->UpdateAmmoTotal(Count);
    }
}

void ASCMarinePlayerController::ArmRestartLevel()
// Player is dead, bind leftclick to restart level on death
{
    UEnhancedInputComponent* EnhancedInputComponent = FindComponentByClass<UEnhancedInputComponent>();
    if (EnhancedInputComponent)
    {
        EnhancedInputComponent->BindAction(IA_RestartLevel, ETriggerEvent::Triggered, this, &ASCMarinePlayerController::RestartLevel);

        if (InputComponent == nullptr)
        {
            UE_LOG(LogTemp, Warning, TEXT("Bind Action Null"));
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Restart Armed"));
        }
    }

}

void ASCMarinePlayerController::RestartLevel()
{
    UGameplayStatics::OpenLevel(this, FName(*UGameplayStatics::GetCurrentLevelName(this)));
}
