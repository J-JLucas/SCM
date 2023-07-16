// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameMenu.generated.h"

/**
 * 
 */
UCLASS()
class SCMARINE_API UGameMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	//UGameMenu(const FObjectInitializer& ObjectInitializer);

protected:

	UFUNCTION()
		void OnPauseClicked();

	UFUNCTION()
		void OnControlsClicked();

	UFUNCTION()
		void OnRestartClicked();

	UFUNCTION()
		void OnExitClicked();

	UFUNCTION(BlueprintCallable)
		void OnReturnClicked();

public:
	
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget, OptionalWidget = true))
	class UButton* PauseButton;

	UPROPERTY(meta = (BindWidget, OptionalWidget = true))
	class UButton* ControlsButton;

	UPROPERTY(meta = (BindWidget, OptionalWidget = true))
	class UButton* RestartButton;

	UPROPERTY(meta = (BindWidget, OptionalWidget = true))
	class UButton* ExitButton;

	UPROPERTY(meta = (BindWidget, OptionalWidget = true))
	class UButton* ReturnButton;


};
