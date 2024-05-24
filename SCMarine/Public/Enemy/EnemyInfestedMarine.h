// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SCMEnemyRanged.h"
#include "EnemyInfestedMarine.generated.h"

/**
 * 
 */
UCLASS()
class SCMARINE_API AEnemyInfestedMarine : public ASCMEnemyRanged
{
	GENERATED_BODY()

public:

	AEnemyInfestedMarine();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	class URadialForceComponent* RadialForce;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	class UParticleSystem* ExplosionEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	float ExplosionDamage{ 100.0f };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	float ExplosionRadius = {600.0f};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	float ExplosionStrength{ 3000.0f };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	float ImpulseStrength{ 500.0f };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	float CountDownTime{0.3f};
	FTimerHandle ExplosionTimer;

	virtual void MeleeAttack() override;
	void Explode();
	virtual void RangedAttack() override;
};
