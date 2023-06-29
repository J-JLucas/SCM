// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SCMWeapon.h"
#include "SCMHitScanWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SCMARINE_API ASCMHitScanWeapon : public ASCMWeapon
{
	GENERATED_BODY()

public:

	//ASCMHitScanWeapon();

	UPROPERTY(EditAnywhere, Category = ImpactDecal)
	class UMaterialInterface* ImpactDecal;

	UPROPERTY(EditAnywhere, Category = BloodDecal)
	class UMaterialInterface* BloodDecal;

	void SetImpactDecal(FString Path);

	void SetBloodDecal(FString Path);
	
	virtual void TraceForward(APlayerController* PController, AActor* PossessedActor);

	virtual void PrimaryFire(APlayerController* PController, AActor* PossessedActor) override;
};
