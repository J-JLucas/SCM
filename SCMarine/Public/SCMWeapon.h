// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SCMWeapon.generated.h"

UENUM(BlueprintType)
enum WeaponType
{
	Melee UMETA(DisplayName = "Melee"),		// not implemented unreal enum requires a 0 element
	Special UMETA(DisplayName = "Special"),
	Shotgun UMETA(DisplayName = "Shotgun"),
	Rifle UMETA(DisplayName = "Rifle"),
	Sniper UMETA(DisplayName = "Sniper"),
	RocketL UMETA(DisplayName = "RocketLauncher"),
	FThrower UMETA(DisplayName = "Flamethrower"),

};


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
	UPROPERTY()
	FText Name;
	float FireRate = 1.0f;
	float ReloadRate = 1.0f;
	float Range = 10000.0f;
	bool bPiercing = false;
	bool bIsFiring = false;
	bool bIsReloading = false;
	//bool bCanDoSwitchy;

	// AmmoProperties
	int MaxAmmo = 600;
	int CurrentAmmo = 150;
	int MaxMag = 50;
	int CurrentMag = 50;

	// sfx
	UPROPERTY(EditAnywhere, Category = Sound)
	class USoundBase* GunshotSound;

	FTimerHandle FireHandle;
	virtual void StartFiring();
	virtual void StopFiring();

	FTimerHandle ReloadHandle;
	virtual void StartReloading();
	virtual void StopReloading();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PrimaryFire(APlayerController* PController, AActor* PossessedActor);

	virtual void AltFire();

	virtual void ReloadWeapon(AActor* PossessedActor);

	bool AddAmmo(int Amount);

	// Gunshot Sound
	UPROPERTY(EditAnywhere, Category = "Sound")
	class USoundBase* Gunshot;

	UPROPERTY()
	bool bCanSwitchWeapons;
	FORCEINLINE bool GetAbleToSwitch() { return bCanSwitchWeapons; }
	void SetAbleToSwitch(bool Status);

	void PlayGunshotSFX(AActor* PossessedActor);
	void SetGunshotSFX(FString Path);
	void PlayFireAnimation(AActor* PossessedActor);

	// Reload Sound
	//UPROPERTY(EditAnywhere, Category = "Sound")
	//	class USoundBase* Reload;

	void SetDamageAmount(float Damage);
	void SetRangeAmount(float RangeValue);
	FORCEINLINE float GetDamageAmount() const { return DamageAmount; }
	FORCEINLINE float GetMaxAmmo() const { return MaxAmmo; }
	FORCEINLINE float GetCurrentAmmo() const { return CurrentAmmo; }
	FORCEINLINE float GetMaxMag() const { return MaxMag; }
	FORCEINLINE float GetCurrentMag() const { return CurrentMag; }
	FORCEINLINE FText GetWeaponName() const { return Name; }

	FORCEINLINE bool GetIsReloading() const { return bIsReloading; }
	
	void UpdateMagString();
	void UpdateAmmoString();
};
