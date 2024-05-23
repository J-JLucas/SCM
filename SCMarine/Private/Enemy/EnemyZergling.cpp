// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyZergling.h"
#include "HealthComponent.h"

AEnemyZergling::AEnemyZergling()
	:Super()
{
	float MaxHealth = (50.0f);
	HealthComponent->SetMaxHealth(MaxHealth);

}
