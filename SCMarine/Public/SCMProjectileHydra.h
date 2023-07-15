// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SCMProjectile.h"
#include "SCMProjectileHydra.generated.h"

/**
 * 
 */
UCLASS()
class SCMARINE_API ASCMProjectileHydra : public ASCMProjectile
{
	GENERATED_BODY()
	
public:

	ASCMProjectileHydra();

	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

};
