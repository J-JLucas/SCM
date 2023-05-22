// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SCM_PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class SCMARINE_API ASCM_PlayerHUD : public AHUD
{
	GENERATED_BODY()
	
protected:

	// Set Crosshair at center of the screen
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* CrosshairTexture;

public:

	// Primary draw call for the entire HUD
	virtual void DrawHUD() override;

};
