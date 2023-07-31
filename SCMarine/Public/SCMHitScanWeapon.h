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

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	class UNiagaraSystem* BloodEffect;

	UPROPERTY(EditAnywhere, Category = Impulse)
	float ImpulseStrength = 400.0f;

	void SetImpactDecal(FString Path);

	void SetBloodDecal(FString Path);

	void SetBloodEffect(FString Path);
	
	virtual void TraceForward(APlayerController* PController, AActor* PossessedActor);

	virtual void PrimaryFire(APlayerController* PController, AActor* PossessedActor) override;
};
