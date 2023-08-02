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

	UPROPERTY()
	class UVictoryHUD* VictoryHUD;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* IC_PlayerChar;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	//class UInputMappingContext* IC_VictoryScreen;

	/** Menu */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* IA_GameMenu;

	/** OnDeath Restart Level */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* IA_RestartLevel;

	/** OnVictory Go Next Level */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* IA_NextLevel;

public:

	UPROPERTY(EditDefaultsOnly);
	TSubclassOf<class UGameMenu> BP_GameMenu;

	void ShowGameMenu();
	void HideGameMenu();
	UFUNCTION(BlueprintCallable)
	void HidePlayerHud();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UHUDWidget> BP_PlayerHUD;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UVictoryHUD> BP_VictoryHUD;

	void UpdateHealthPercent(float HealthPercent);
	void UpdateActiveWeaponName(FText name);
	void UpdateMagCount(float Count);
	void UpdateAmmoCount(float Count);

	UFUNCTION(BlueprintCallable)
	void ArmRestartLevel();
	void RestartLevel();

	UFUNCTION(BlueprintCallable)
	void ShowVictoryScreen();
	void ArmNextLevel();
	void GoNextLevel();

	UFUNCTION(BlueprintCallable)
	void PrintActivityFeedMessage(const FString& Message);

	UFUNCTION(BlueprintCallable)
	void PrintInstructionalMessage(const FString& Message);

	UFUNCTION(BlueprintCallable)
	void PrintKeycard(enum KeyType Key);


};
