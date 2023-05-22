// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyZergling.h"
#include "HealthComponent.h"

AEnemyZergling::AEnemyZergling()
	:Super()
{
	float MaxHealth = (100.0f);
	// Init Health Component
	//HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	HealthComponent->SetMaxHealth(MaxHealth);

}
