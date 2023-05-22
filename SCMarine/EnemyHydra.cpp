// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyHydra.h"
#include "HealthComponent.h"

AEnemyHydra::AEnemyHydra()
	:Super()
{
	float MaxHealth = (200.0f);
	// Init Health Component
	//HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	HealthComponent->SetMaxHealth(MaxHealth);

}

