// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SCMWeapon.generated.h"

UCLASS()
class SCMARINE_API ASCMWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASCMWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// GunProperties
	UPROPERTY()
	float DamageAmount = 25.0f;
	float FireRate = 1.0f;
	float Range = 10000.0f;
	bool Piercing = false;

	// AmmoProperties
	int MaxAmmo = 600.0f;
	int CurrentAmmo = 150.0f;
	int MagMax = 50;
	int MagCurrent = 50;

	// sfx
	UPROPERTY(EditAnywhere, Category = Sound)
	class USoundBase* GunshotSound;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PrimaryFire(APlayerController* PController, AActor* PossessedActor);

	virtual void AltFire();

	virtual void ReloadWeapon();

	// Gunshot Sound
	UPROPERTY(EditAnywhere, Category = "Sound")
	class USoundBase* Gunshot;

	void PlayGunshotSFX(AActor* PossessedActor);
	void SetGunshotSFX(FString Path);

	// Reload Sound
	//UPROPERTY(EditAnywhere, Category = "Sound")
	//	class USoundBase* Reload;

	void SetDamageAmount(float Value);
	FORCEINLINE float GetDamageAmount() const { return DamageAmount; }
};
