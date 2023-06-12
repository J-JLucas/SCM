// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "Public/HealthInterface.h"
#include "SCMPlayerCharacter.generated.h"

UENUM(BlueprintType)
enum WeaponType
{
	Melee UMETA(DisplayName = "Melee"),		// not implemented unreal enum requires a 0 element
	Special UMETA(DisplayName = "Special"),
	Pistol UMETA(DisplayName = "Pistol"),
	Shotgun UMETA(DisplayName = "Shotgun"),
	Rifle UMETA(DisplayName = "Rifle"),
	Sniper UMETA(DisplayName = "Sniper"),
	RocketL UMETA(DisplayName = "RocketLauncher"),
	FThrower UMETA(DisplayName = "Flamethrower"),

};

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
		class UInputAction* IA_SwitchPistol;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* IA_SwitchShotgun;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* IA_SwitchRifle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* IA_SwitchSniper;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* IA_SwitchRL;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* IA_SwitchFL;

public:
	// Sets default values for this character's properties
	ASCMPlayerCharacter();

	void PostInitializeComponents();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for look input */
	void Look(const FInputActionValue& Value);	

	// Fire gun
	void Fire();

	// Reload current gun
	void ReloadActiveWeapon();

	// Switch active weapon
	void SwitchWeapon(WeaponType NewWeapon);

	void UpdateWeaponString(FText Name);

	// Player Health
	float MaxHealth = 100.0f;

	/*
	FTimerHandle SwitchWeaponHandle;
	virtual void StartSwitching(WeaponType NewWeapon);
	virtual void StopSwitching(WeaponType NewWeapon);
	bool bIsSwitching = false;
	float SwitchDelay = 0.5f;
	*/

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// FPS camera
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FPSCameraComponent;

	// FPS mesh (arms); visible only to owning player
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* FPSMesh;

	// Health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthComponent")
	class UHealthComponent* HealthComponent;

	virtual void OnDeath_Implementation() override;
	virtual void OnTakeDamage_Implementation() override;

	// Weapons
	UPROPERTY(EditAnywhere, Category = "Weapons")
	TArray<ASCMWeapon*> Arsenal;

	UPROPERTY(VisibleAnywhere)
	TEnumAsByte<WeaponType> ActiveWeapon;

	UPROPERTY(VisibleAnywhere)
	class AHSRifle* wMelee;

	UPROPERTY(VisibleAnywhere)
	class AHSPistol* wPistolPlayer;
	USkeletalMesh* PistolMesh;
	FString PistolMeshPath = R"('/Game/Models/Guns/2_Pistol/Deagle_Sk.Deagle_Sk')";
	
	UPROPERTY(VisibleAnywhere)
	class AHSShotgun* wShotgunPlayer;
	USkeletalMesh* ShotgunMesh;
	FString ShotgunMeshPath = R"('/Game/Models/Guns/3_Shotgun/Shotgun_SkMesh.Shotgun_SkMesh')";

	UPROPERTY(Instanced, BlueprintReadOnly, Category = "Guns")
	class AHSRifle* wRiflePlayer;
	USkeletalMesh* RifleMesh;
	FString RifleMeshPath = R"('/Game/Models/Guns/4_GaussRifle/ReynorRifle_SkMesh.ReynorRifle_SkMesh')";

	UPROPERTY(VisibleAnywhere)
	class AHSSniper* wSniperPlayer;
	USkeletalMesh* SniperMesh;
	FString SniperMeshPath = R"('/Game/Models/Guns/5_SniperRifle/Sniper_SkeletalMesh.Sniper_SkeletalMesh')";

	UPROPERTY(VisibleAnywhere)
	class APRocketLauncher* wRocketLPlayer;
	USkeletalMesh* RocketLMesh;
	FString RocketLMeshPath = R"('/Game/Models/Guns/6_RocketLauncher/Marauder_Gun.Marauder_Gun')";

	UPROPERTY(VisibleAnywhere)
	class APFlameThrower* wFThrowerPlayer;
	USkeletalMesh* FThrowerMesh;
	FString FThrowerMeshPath = R"('/Game/Models/Guns/7_FlameThrower/Flamethrower_Export_LP.Flamethrower_Export_LP')";


	// PlayerController & Pawn References
	UPROPERTY(VisibleAnywhere)
	class APlayerController* PController;
	
	// This is so embarassing... These two need to be combined...
	//UPROPERTY(VisibleAnywhere)
	//class ASCMarinePlayerController* SCMPController;

	UPROPERTY(VisibleAnywhere)
	class AActor* PossessedActor;

};
