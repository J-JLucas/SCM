// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class SCMARINE_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	// Set Crosshair at center of the screen
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* CrosshairTexture;

	// Update HealthBar
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* HealthText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MagTotalText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* AmmoTotalText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* WeaponText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CenterMessageText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* LeftMessageText;

	void UpdateHealthPercent(float HealthPercent);
	void UpdateMagazine(float numBullets);
	void UpdateAmmoTotal(float numBullets);
	void UpdateWeaponText(FText Name);

	UFUNCTION(BlueprintCallable)
	void PrintMessageToPlayer(FText Message);
	

};
