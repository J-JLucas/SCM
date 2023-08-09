// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "Public/HealthInterface.h"
#include "Public/SCMWeapon.h"
#include "SCMPlayerCharacter.generated.h"

class ASCMWeapon;

UCLASS()
class SCMARINE_API ASCMPlayerCharacter : public ACharacter, public IHealthInterface
{
	GENERATED_BODY()

private:

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputMappingContext* IC_PlayerChar;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* IA_Movement;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* IA_Look;

	//** Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* IA_Fire;

	//** Reload Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* IA_Reload;

	//** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* IA_Jump;

	//** Switch Weapon Input Actions */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* IA_SwitchSpecial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* IA_SwitchShotgun;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* IA_SwitchRifle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* IA_SwitchSniper;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* IA_SwitchRL;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* IA_SwitchFT;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* IA_Flashlight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* IA_AltFire;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* IA_Nightvision;

public:
	// Sets default values for this character's properties
	ASCMPlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for look input */
	void Look(const FInputActionValue& Value);	

	// flashlight
	UPROPERTY(BlueprintReadWrite, Category = Flashlight)
	class USpotLightComponent* Flashlight;
	UPROPERTY(EditAnywhere, Category = Flashlight)
	class USoundBase* FlashlightClickSound;
	bool FlashlightOn = false;
	void ActivateFlashlight();

	// Fire gun
	void Fire();
	void AltFire();

	// Reload current gun
	void ReloadActiveWeapon();

	// Switch active weapon
	void SwitchWeapon(WeaponType NewWeapon);
	void UpdateWeaponString(FText Name);

	// Player Health
	float MaxHealth = 100.0f;

	FTimerHandle SwitchWeaponHandle;
	virtual void StartSwitching();
	virtual void StopSwitching();
	bool bIsSwitching = false;
	float SwitchDelay = 0.3f;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// FPS camera
	//UPROPERTY(VisibleAnywhere)
	UPROPERTY(BlueprintReadWrite)
	UCameraComponent* FPSCameraComponent;

	// FPS mesh (arms); visible only to owning player
	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* FPSMeshRefresh;

	// Health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthComponent")
	class UHealthComponent* HealthComponent;

	virtual void OnDeath_Implementation() override;

	virtual void OnTakeDamage_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, Category = Animation)
	void OnFireEvent();
	void OnFireEvent_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = Animation)
	void OnReloadEvent();
	void OnReloadEvent_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = Animation)
	void OnSwitchGunEvent();
	void OnSwitchGunEvent_Implementation();

	// Weapons
	UPROPERTY(EditAnywhere, Category = "Weapons")
	TArray<ASCMWeapon*> Arsenal;

	UPROPERTY(EditAnywhere, Category = "Weapons")
	TArray<bool> UnlockedGuns;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TEnumAsByte<WeaponType> ActiveWeapon;

	UPROPERTY(VisibleAnywhere)
	class AHSRifle* wMelee;
		
	UPROPERTY(VisibleAnywhere)
	class AHSShotgun* ShotgunPlayer;
	USkeletalMesh* ShotgunMesh;
	FString ShotgunMeshPath = R"('/Game/Models/Guns/3_Shotgun/Shotgun_SkMesh.Shotgun_SkMesh')";

	UPROPERTY(Instanced, BlueprintReadOnly, Category = "Guns")
	class AHSRifle* RiflePlayer;
	USkeletalMesh* RifleMesh;
	FString RifleMeshPath = R"('/Game/Models/Guns/4_GaussRifle/GaussRifleFinal.GaussRifleFinal')";
	
	UPROPERTY(VisibleAnywhere)
	class AHSSniper* SniperPlayer;
	USkeletalMesh* SniperMesh;
	FString SniperMeshPath = R"('/Game/Models/Guns/5_SniperRifle/SniperRifle.SniperRifle')";

	UPROPERTY(VisibleAnywhere)
	class APRocketLauncher* RocketLPlayer;
	USkeletalMesh* RocketLMesh;
	FString RocketLMeshPath = R"('/Game/Models/Guns/6_RocketLauncher/Marauder_Gun.Marauder_Gun')";

	UPROPERTY(VisibleAnywhere)
	class APFlameThrower* FThrowerPlayer;
	USkeletalMesh* FThrowerMesh;
	FString FThrowerMeshPath = R"('/Game/Models/Guns/7_FlameThrower/Flamethrower_Export_LP.Flamethrower_Export_LP')";

	// PlayerController & Pawn References
	UPROPERTY(VisibleAnywhere)
	

	class APlayerController* PController;
	
	UPROPERTY(VisibleAnywhere)
	class AActor* PossessedActor;

	bool HealPlayer(float Value);
	bool PickupAmmo(WeaponType AmmoType, int Amount);
	bool PickupWeapon(WeaponType WeaponType, int Amount);

	UPROPERTY(BlueprintReadWrite, Category = "Controls")
	float MouseSense{1.0f};

	UPROPERTY(BlueprintReadWrite)
	bool bOnLadder{false};

	// Keys
	UPROPERTY(BlueprintReadOnly)
	TArray<bool> KeyArray;

	void GiveKey(enum KeyType Key);
	FORCEINLINE bool CheckHasKey(enum KeyType Key) { return KeyArray[Key]; }

	UPROPERTY(EditAnywhere, Category = "Stimpack")
	float StimLength{ 30.0f };
	FTimerHandle StimTimerHandle;
	bool StimActive{ false };

	UFUNCTION(BlueprintCallable)
	void ActivateStim();
	void DisableStim();

	void CamZoomIn();
	void CamZoomOut();


	//class UPostProcessComponent* PostProcessComponent;
	
	//UPROPERTY(EditAnywhere, Category = Nightvision)
	//FPostProcessSettings DefaultPP;
	
	//UPROPERTY(EditAnywhere, Category = Nightvision)
	//FPostProcessSettings NightvisionPP;

	UFUNCTION(BlueprintImplementableEvent)
	void TurnOnNightvision();
	void TurnOnNightvision_Implementation();

	UFUNCTION(BlueprintImplementableEvent)
	void TurnOffNightvision();
	void TurnOffNightvision_Implementation();
	void Nightvision();
	
	UPROPERTY(EditAnywhere, Category = Nightvision)
	class USoundBase* NightvisionOnSFX;

};
