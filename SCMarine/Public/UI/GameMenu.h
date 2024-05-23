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
		void OnSavedClicked();

	UFUNCTION()
		void OnLoadClicked();

	UFUNCTION()
		void OnOptionsClicked();

	UFUNCTION()
		void OnRestartClicked();

	UFUNCTION()
		void OnQuitToMenuClicked();

	UFUNCTION()
		void OnExitClicked();

	UFUNCTION()
		void OnInputClicked();

	UFUNCTION()
		void OnSoundClicked();

	UFUNCTION()
		void OnDisplayClicked();

	UFUNCTION()
		void OnBackMainClicked();

	UFUNCTION()
		void OnBackOptionsClicked();

	UFUNCTION(BlueprintCallable)
		void OnReturnClicked();

	UFUNCTION()
		void SwitchCanvas(int32 CanvasIndex);

	//UFUNCTION()
	//void OnMouseSensSliderValueChanged(float NewValue);

	//UFUNCTION()
	//void OnMouseSensEditableTextChanged(const FText& NewText);


	const int32 BaseMenu{ 0 };
	const int32 OptionsMenu{ 1 };
	const int32 InputMenu{ 2 };
	const int32 SoundMenu{ 3 };
	const int32 DisplayMenu{ 4 };

public:
	
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget, OptionalWidget = true))
	class UButton* SaveButton;

	UPROPERTY(meta = (BindWidget, OptionalWidget = true))
	class UButton* LoadButton;

	UPROPERTY(meta = (BindWidget, OptionalWidget = true))
	class UButton* OptionsButton;

	UPROPERTY(meta = (BindWidget, OptionalWidget = true))
	class UButton* OptionsBackButton;

	UPROPERTY(meta = (BindWidget, OptionalWidget = true))
	class UButton* RestartButton;

	UPROPERTY(meta = (BindWidget, OptionalWidget = true))
	class UButton* QuitToMenuButton;

	UPROPERTY(meta = (BindWidget, OptionalWidget = true))
	class UButton* ExitButton;

	UPROPERTY(meta = (BindWidget, OptionalWidget = true))
	class UButton* ReturnButton;

	UPROPERTY(meta = (BindWidget, OptionalWidget = true))
	class UButton* InputButton;
	
	UPROPERTY(meta = (BindWidget, OptionalWidget = true))
	class UButton* SoundButton;
	
	UPROPERTY(meta = (BindWidget, OptionalWidget = true))
	class UButton* DisplayButton;

	UPROPERTY(meta = (BindWidget, OptionalWidget = true))
	class UButton* InputBackButton;

	UPROPERTY(meta = (BindWidget, OptionalWidget = true))
	class UButton* SoundBackButton;

	UPROPERTY(meta = (BindWidget, OptionalWidget = true))
	class UButton* DisplayBackButton;

	//UPROPERTY(meta = (BindWidget, OptionalWidget = true))
	//class USlider* MouseSensSlider;

	//UPROPERTY(meta = (BindWidget, OptionalWidget = true))
	//class UEditableText* MouseSensEditableText;

	UPROPERTY(meta = (BindWidget, OptionalWidget = true))
	class UWidgetSwitcher* DaWidgetSwitcher;

};
