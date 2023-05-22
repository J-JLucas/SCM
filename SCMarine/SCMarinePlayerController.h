// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SCMarinePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SCMARINE_API ASCMarinePlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:

	UPROPERTY()
	class UGameMenu* GameMenu;

	UPROPERTY()
	class UHUDWidget* HUDWidget;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* IC_PlayerChar;

	/** Menu */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* IA_GameMenu;

public:

	UPROPERTY(EditDefaultsOnly);
	TSubclassOf<class UGameMenu> BP_GameMenu;


	void ShowGameMenu();
	void HideGameMenu();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UHUDWidget> BP_PlayerHUD;

	void UpdateHealthPercent(float HealthPercent);

};
