// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUDWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextRenderComponent.h"
#include "Components/TextBlock.h"
#include "Pickups/PickableActor_Keycard.h"

void UHUDWidget::UpdateHealthPercent(float HealthPercent)
{
	HealthBar->SetPercent(HealthPercent);
	int HealthNum = (int)(HealthPercent*100);
	HealthText->SetText(FText::AsNumber(HealthNum));
	return;
}

void UHUDWidget::UpdateMagazine(float numBullets)
{
	int Bullets = (int)numBullets;
	MagTotalText->SetText(FText::AsNumber(Bullets));
	return;
}

void UHUDWidget::UpdateAmmoTotal(float numBullets)
{
	int Bullets = (int)numBullets;
	if (Bullets < 100) 
	{
		AmmoTotalText->SetText(FText::FromString("| " + FString::FromInt(Bullets)));
	}
	else
	{
		AmmoTotalText->SetText(FText::FromString("|" + FString::FromInt(Bullets)));
	}
	return;
}

void UHUDWidget::UpdateWeaponText(FText Name)
{
	WeaponText->SetText(Name);
	return;
}

void UHUDWidget::UpdateActivity_Implementation(const FString& Message)
{
}

void UHUDWidget::UpdateInstructional_Implementation(const FString& Message)
{
}

void UHUDWidget::DrawScope_Implementation()
{
}

void UHUDWidget::HideScope_Implementation()
{
}

void UHUDWidget::UpdateKeyCardIcon_Implementation(KeyType Key)
{
}
