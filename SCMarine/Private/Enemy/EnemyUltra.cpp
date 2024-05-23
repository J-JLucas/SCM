// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyUltra.h"
#include "HealthComponent.h"

AEnemyUltra::AEnemyUltra()
	:Super()
{
	float MaxHealth = (1000.0f);
	// Init Health Component
	//HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	HealthComponent->SetMaxHealth(MaxHealth);

}


