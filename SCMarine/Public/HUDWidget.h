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

	void UpdateHealthPercent(float HealthPercent);
	void UpdateMagazine(float numBullets);
	void UpdateAmmoTotal(float numBullets);
	void UpdateWeaponText(FText Name);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateActivityMessage(const FString& Message);
	void UpdateActivity_Implementation(const FString& Message);
	
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateInstructionalMessage(const FString& Message);
	void UpdateInstructional_Implementation(const FString& Message);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateKeyCardIcon(enum KeyType Key);
	void UpdateKeyCardIcon_Implementation(enum KeyType Key);
};
