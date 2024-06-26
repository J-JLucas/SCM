// Fill out your copyright notice in the Description page of Project Settings.


#include "SCMPlayerCharacter.h"
#include "SCMarinePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CapsuleComponent.h"
#include "HealthComponent.h"
#include "Enemy/SCMEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "Weapons/SCMWeapon.h"
#include "Weapons/HSShotgun.h"
#include "Weapons/HSRifle.h"
#include "Weapons/HSSniper.h"
#include "Weapons/PRocketLauncher.h"
#include "Weapons/PFlameThrower.h"
#include "Components/SpotLightComponent.h"
#include "Level/LockableDoor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"

// Sets default values
ASCMPlayerCharacter::ASCMPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Instantiate FPSCamera
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	check(FPSCameraComponent != nullptr);

	// Attach the camera component to our capsule component.
	FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));

	// Position the camera slightly above the eyes.
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f + BaseEyeHeight));

	// Enable the pawn to control camera rotation.
	FPSCameraComponent->bUsePawnControlRotation = true;

	// Create a first person mesh component for the owning player
	FPSMeshRefresh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	check(FPSMeshRefresh != nullptr);

	// Only owning player can see mesh
	FPSMeshRefresh->SetOnlyOwnerSee(true);

	//Attach the FPS mesh to the FPS camera
	FPSMeshRefresh->SetupAttachment(FPSCameraComponent);

	// Disable environmental shadows to preserve the illusion of having a single mesh
	// (disables the arms' shadow, not the full body shadow that other players can see
	FPSMeshRefresh->bCastDynamicShadow = false;
	FPSMeshRefresh->CastShadow = false;

	// Hide 3rd person mesh from FPS Cam
	GetMesh()->SetOwnerNoSee(true);

	// Init Health Component
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	HealthComponent->SetMaxHealth(MaxHealth);

	// Init Weapon objects
	Arsenal.Init(nullptr, 8);
	KeyArray.Init(false, 4);
	UnlockedGuns.Init(false, 8);

	wMelee = nullptr;

	ShotgunPlayer = CreateDefaultSubobject<AHSShotgun>(TEXT("PlayerShotgun"));
	RiflePlayer = CreateDefaultSubobject<AHSRifle>(TEXT("PlayerRifle"));
	SniperPlayer = CreateDefaultSubobject<AHSSniper>(TEXT("PlayerSniper"));
	RocketLPlayer = CreateDefaultSubobject<APRocketLauncher>(TEXT("PlayerRocketLauncher"));
	FThrowerPlayer = CreateDefaultSubobject<APFlameThrower>(TEXT("PlayerFlameThrower"));

	Flashlight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Flashlight"));
	Flashlight->SetupAttachment(FPSCameraComponent);
	Flashlight->SetRelativeLocation(FVector(16.0f, 0.0f, -9.0f));
	Flashlight->SetIntensity(0.0f);
	Flashlight->SetAttenuationRadius(7000.0f);
	Flashlight->SetOuterConeAngle(20.f);
	Flashlight->SetUseTemperature(true);
	Flashlight->SetTemperature(3500.0f);
	Flashlight->SetUseInverseSquaredFalloff(false);
	Flashlight->SetLightFalloffExponent(15.0f);
		
	SetupStimulusSource();
	//PostProcessComponent = CreateDefaultSubobject<UPostProcessComponent>(TEXT("PostProcessComponent"));
	//FPSCameraComponent->SetupAttachment(PostProcessComponent);

}

// Called when the game starts or when spawned
void ASCMPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Add Input Mapping Context
	PlayerController = Cast<ASCMarinePlayerController>(GetController());
	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(IC_PlayerChar, 1);
		}
	}

	// Initialize Weapons ... need to manually BeginPlay() because
	// they aren't instantiated in the world?
	// Load meshes and insert into Arsenal TArray
	
	ShotgunPlayer->BeginPlay();
	Arsenal.Insert(ShotgunPlayer, WeaponType::Shotgun);
	//ShotgunPlayer->SetOwner(this);
	//ShotgunMesh = LoadObject<USkeletalMesh>(nullptr, *ShotgunMeshPath);

	RiflePlayer->BeginPlay();
	Arsenal.Insert(RiflePlayer, WeaponType::Rifle);
	//RiflePlayer->SetOwner(this);
	//RifleMesh = LoadObject<USkeletalMesh>(nullptr, *RifleMeshPath);

	SniperPlayer->BeginPlay();
	Arsenal.Insert(SniperPlayer, WeaponType::Sniper);
	//SniperPlayer->SetOwner(this);
	//SniperMesh = LoadObject<USkeletalMesh>(nullptr, *SniperMeshPath);
	
	RocketLPlayer->BeginPlay();
	Arsenal.Insert(RocketLPlayer, WeaponType::RocketL);
	//RocketLPlayer->SetOwner(this);
	//RocketLMesh = LoadObject<USkeletalMesh>(nullptr, *RocketLMeshPath);

	FThrowerPlayer->BeginPlay();
	Arsenal.Insert(FThrowerPlayer, WeaponType::FThrower);
	//FThrowerPlayer->SetOwner(this);
	//FThrowerMesh = LoadObject<USkeletalMesh>(nullptr, *FThrowerMeshPath);

	// Default Weapon
	UnlockedGuns[WeaponType::Rifle] = true;
	ActiveWeapon = WeaponType::Rifle;
	SwitchWeapon(WeaponType::Rifle);
	OnSwitchGunEvent();
	
}

// Called every frame
void ASCMPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASCMPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) 
	{
		//Moving
		EnhancedInputComponent->BindAction(IA_Movement, ETriggerEvent::Triggered, this, &ASCMPlayerCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this, &ASCMPlayerCharacter::Look);

		//Fire
		EnhancedInputComponent->BindAction(IA_Fire, ETriggerEvent::Triggered, this, &ASCMPlayerCharacter::Fire);

		//AltFire
		EnhancedInputComponent->BindAction(IA_AltFire, ETriggerEvent::Triggered, this, &ASCMPlayerCharacter::AltFire);

		//Nightvision
		EnhancedInputComponent->BindAction(IA_Nightvision, ETriggerEvent::Triggered, this, &ASCMPlayerCharacter::Nightvision);

		//Reload
		EnhancedInputComponent->BindAction(IA_Reload, ETriggerEvent::Triggered, this, &ASCMPlayerCharacter::ReloadActiveWeapon);
		
		//Jump
		EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &ASCMPlayerCharacter::Jump);
		EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Completed, this, &ASCMPlayerCharacter::StopJumping);

		//Flashlight
		EnhancedInputComponent->BindAction(IA_Flashlight, ETriggerEvent::Triggered, this, &ASCMPlayerCharacter::ActivateFlashlight);
	
		//Switch Weapons
		//EnhancedInputComponent->BindAction(IA_SwitchSpecial, ETriggerEvent::Triggered, this, &ASCMPlayerCharacter::SwitchWeapon, WeaponType::Special);
		EnhancedInputComponent->BindAction(IA_SwitchShotgun, ETriggerEvent::Triggered, this, &ASCMPlayerCharacter::SwitchWeapon, WeaponType::Shotgun);
		EnhancedInputComponent->BindAction(IA_SwitchRifle, ETriggerEvent::Triggered, this, &ASCMPlayerCharacter::SwitchWeapon, WeaponType::Rifle);
		EnhancedInputComponent->BindAction(IA_SwitchSniper, ETriggerEvent::Triggered, this, &ASCMPlayerCharacter::SwitchWeapon, WeaponType::Sniper);
		EnhancedInputComponent->BindAction(IA_SwitchRL, ETriggerEvent::Triggered, this, &ASCMPlayerCharacter::SwitchWeapon, WeaponType::RocketL);
		EnhancedInputComponent->BindAction(IA_SwitchFT, ETriggerEvent::Triggered, this, &ASCMPlayerCharacter::SwitchWeapon, WeaponType::FThrower);
	
	}
}

void ASCMPlayerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput((LookAxisVector.X) * MouseSense * MouseModifierX);
		AddControllerPitchInput((LookAxisVector.Y) * MouseSense * MouseModifierY);
	}
}


void ASCMPlayerCharacter::SetInvertMouseX(bool Status)
{
	if (Status)
	{
		MouseModifierX = -1.0f;
	}
	else
	{
		MouseModifierX = 1.0f;
	}
}

void ASCMPlayerCharacter::SetInvertMouseY(bool Status)
{
	if (Status)
	{
		MouseModifierY = -1.0f;
	}
	else
	{
		MouseModifierY = 1.0f;
	}
}

void ASCMPlayerCharacter::SetupStimulusSource()
{
	StimulusSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus"));
	if (StimulusSource)
	{
		//StimulusSource->bAutoRegister = true;
		StimulusSource->RegisterForSense(UAISense_Sight::StaticClass());
		StimulusSource->RegisterWithPerceptionSystem();
		UE_LOG(LogTemp, Warning, TEXT("StimulusSource Setup Successfully!"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to Setup StimulusSource"));
	}
}

void ASCMPlayerCharacter::ActivateFlashlight()
{
	UE_LOG(LogTemp, Warning, TEXT("Flashlight input received!"));
	if (FlashlightOn)
		{
		//turn off flashlight
		Flashlight->SetIntensity(0.0f);
		FlashlightOn = false;
		UGameplayStatics::PlaySoundAtLocation(this, FlashlightClickSound, GetActorLocation(), 1.0f, 1.0f);
		}
	else
	{
		//turn on flashlight
		Flashlight->SetIntensity(25.0f);
		FlashlightOn = true;
		UGameplayStatics::PlaySoundAtLocation(this, FlashlightClickSound, GetActorLocation(), 1.0f, 1.0f);
	}
}

void ASCMPlayerCharacter::Move(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("Movement Input Recieved"));
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (!Controller) { return; }

	if (bOnLadder) 
		{
		AddMovementInput(GetActorUpVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
		}

	else
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}


void ASCMPlayerCharacter::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Fire input received!"));

	if (bIsSwitching) { return; }

	switch (ActiveWeapon)
	{
		case(WeaponType::Special):
		{
			UE_LOG(LogTemp, Warning, TEXT("Fired Special"));
			break;
		}
		case(WeaponType::Shotgun):
		{
			Arsenal[WeaponType::Shotgun]->PrimaryFire();
			UE_LOG(LogTemp, Warning, TEXT("Fired Shotgun"));
			break;
		}
		case(WeaponType::Rifle):
		{
			Arsenal[WeaponType::Rifle]->PrimaryFire();
			UE_LOG(LogTemp, Warning, TEXT("Fired GaussRifle"));
			break;
		}
		case(WeaponType::Sniper):
		{
			Arsenal[WeaponType::Sniper]->PrimaryFire();
			UE_LOG(LogTemp, Warning, TEXT("Fired SniperRifle"));
			break;
		}
		case(WeaponType::RocketL):
		{
			Arsenal[WeaponType::RocketL]->PrimaryFire();
			UE_LOG(LogTemp, Warning, TEXT("Fired RocketLauncher"));
			break;
		}
		case(WeaponType::FThrower):
		{	
			Arsenal[WeaponType::FThrower]->PrimaryFire();
			UE_LOG(LogTemp, Warning, TEXT("Fired FlameThrower"));
			break;
		}
	}
}

void ASCMPlayerCharacter::AltFire()
{
	if (bIsSwitching) { return; }
	if (Arsenal[ActiveWeapon]->GetIsReloading() == true) { return; }
	Arsenal[ActiveWeapon]->AltFire();

}

void ASCMPlayerCharacter::ReloadActiveWeapon()
{
	UE_LOG(LogTemp, Warning, TEXT("Reload Input Recieved"));
	if (Arsenal[ActiveWeapon]->GetIsReloading() == true) { return; }
	if (bIsSwitching) { return; }
	Arsenal[ActiveWeapon]->ReloadWeapon();

}

void ASCMPlayerCharacter::SwitchWeapon(WeaponType NewWeapon)
{
	if (ActiveWeapon == NewWeapon) { return; };
	if (UnlockedGuns[NewWeapon] == false) { return; }		// Player doesn't have gun
	
	// AbleToSwitch basically represents if the gunObject is busy firing reloading etc...
	bool result = Arsenal[ActiveWeapon]->GetAbleToSwitch();
	if (result)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We Good"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Can't switch guns rn"));
		return;
	}

	AHSSniper* IsSniper = Cast<AHSSniper>(Arsenal[ActiveWeapon]);
	
	if (IsSniper)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, "Sniper Was equipped");
		if (IsSniper->GetIsScopedIn())
		{
			IsSniper->AltFire();
		}
	}
	ActiveWeapon = NewWeapon;
	StartSwitching();

}

void ASCMPlayerCharacter::UpdateWeaponString(FText Name)
{
	if (PlayerController)
	{
		PlayerController->UpdateActiveWeaponName(Name);
	}
}

void ASCMPlayerCharacter::StartSwitching()
{
	bIsSwitching = true;
	GetWorldTimerManager().SetTimer(SwitchWeaponHandle, this, &ASCMPlayerCharacter::StopSwitching, SwitchDelay, false);
	OnSwitchGunEvent();		// event trigger for blueprint animations
	return;
}

void ASCMPlayerCharacter::StopSwitching()
{
	GetWorldTimerManager().ClearTimer(SwitchWeaponHandle);
	bIsSwitching = false;

	switch (ActiveWeapon)
	{
		case(WeaponType::Special):
		{
			UE_LOG(LogTemp, Warning, TEXT("Switched To Special"));
			break;
		}

		case(WeaponType::Shotgun):
		{
			//FPSMesh->SetSkeletalMesh(ShotgunMesh);
			//FPSMesh->AddRelativeLocation(FVector(46.0f, -20.0f, -98.0f));
			//FPSMesh->AddRelativeRotation(FRotator(4.0f, -86.0f, -50.0f));
			UpdateWeaponString(Arsenal[WeaponType::Shotgun]->GetWeaponName());
			Arsenal[WeaponType::Shotgun]->UpdateMagString();
			Arsenal[WeaponType::Shotgun]->UpdateAmmoString();
			UE_LOG(LogTemp, Warning, TEXT("Switched To Shotgun"));
			break;
		}
		case(WeaponType::Rifle):
		{
			//FPSMesh->SetSkeletalMesh(RifleMesh);
			//FPSMesh->AddRelativeLocation(FVector(2.0f, 48.0f, -58.0f));
			//FPSMesh->AddRelativeRotation(FRotator(0.0f, -88.0f, -1.0f));
			UpdateWeaponString(Arsenal[WeaponType::Rifle]->GetWeaponName());
			Arsenal[WeaponType::Rifle]->UpdateMagString();
			Arsenal[WeaponType::Rifle]->UpdateAmmoString();
			UE_LOG(LogTemp, Warning, TEXT("Switched To GaussRifle"));
			break;
		}
		case(WeaponType::Sniper):
		{
			//FPSMesh->SetSkeletalMesh(SniperMesh);
			//FPSMesh->AddRelativeLocation(FVector(45.0f, 24.0f, -42.0f));
			//FPSMesh->AddRelativeRotation(FRotator(0.0f, -90.0, 0.0f));
			UpdateWeaponString(Arsenal[WeaponType::Sniper]->GetWeaponName());
			Arsenal[WeaponType::Sniper]->UpdateMagString();
			Arsenal[WeaponType::Sniper]->UpdateAmmoString();
			UE_LOG(LogTemp, Warning, TEXT("Switched To SniperRifle"));
			break;
		}
		case(WeaponType::RocketL):
		{
			//FPSMesh->SetSkeletalMesh(RocketLMesh);
			//FPSMesh->AddRelativeLocation(FVector(180.0f, 29.0f, -128.0f));
			//FPSMesh->AddRelativeRotation(FRotator(-85.0f, -73.0, 238.0f));
			UpdateWeaponString(Arsenal[WeaponType::RocketL]->GetWeaponName());
			Arsenal[WeaponType::RocketL]->UpdateMagString();
			Arsenal[WeaponType::RocketL]->UpdateAmmoString();
			UE_LOG(LogTemp, Warning, TEXT("Switched To RocketLauncher"));
			break;
		}
		case(WeaponType::FThrower):
		{
			//FPSMesh->SetSkeletalMesh(FThrowerMesh);
			//FPSMesh->AddRelativeLocation(FVector(21.0f, 22.0f, -37.0f));
			//FPSMesh->AddRelativeRotation(FRotator(-3.0f, -0.5, 0.0f));
			UpdateWeaponString(Arsenal[WeaponType::FThrower]->GetWeaponName());
			Arsenal[WeaponType::FThrower]->UpdateMagString();
			Arsenal[WeaponType::FThrower]->UpdateAmmoString();
			UE_LOG(LogTemp, Warning, TEXT("Switched To FlameThrower"));
			break;
		}
	}


}

void ASCMPlayerCharacter::OnDeath_Implementation()
{
	if (PlayerController)
	{
		DisableInput(PlayerController);
	}
	FPSMeshRefresh->SetOwnerNoSee(true);
	SetCanBeDamaged(false);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "PlayerCharacter Destroyed");
}

void ASCMPlayerCharacter::OnTakeDamage_Implementation()
{

	if (PlayerController)
	{
		PlayerController->UpdateHealthPercent(HealthComponent->GetHealthPercent());
	}

}

void ASCMPlayerCharacter::OnFireEvent_Implementation()
{
}

void ASCMPlayerCharacter::OnReloadEvent_Implementation()
{
}

void ASCMPlayerCharacter::OnSwitchGunEvent_Implementation()
{
}

bool ASCMPlayerCharacter::HealPlayer(float Value)
{
	bool Success = HealthComponent->AddHealth(Value);

	if (Success) 
	{
		if (PlayerController)
		{
			PlayerController->UpdateHealthPercent(HealthComponent->GetHealthPercent());
		}
		return true;
	}
	else
	{
		return false;	// health already at max
	}
}

bool ASCMPlayerCharacter::PickupAmmo(WeaponType AmmoType, int Amount)
{
	bool Success;
	switch (AmmoType)
	{

		case(WeaponType::Shotgun):
		{
			Success = Arsenal[WeaponType::Shotgun]->AddAmmo(Amount);
			break;
		}
		case(WeaponType::Rifle):
		{
			Success = Arsenal[WeaponType::Rifle]->AddAmmo(Amount);
			break;
		}
		case(WeaponType::Sniper):
		{
			Success = Arsenal[WeaponType::Sniper]->AddAmmo(Amount);
			break;
		}
		case(WeaponType::RocketL):
		{
			Success = Arsenal[WeaponType::RocketL]->AddAmmo(Amount);
			break;
		}
		case(WeaponType::FThrower):
		{
			Success = Arsenal[WeaponType::FThrower]->AddAmmo(Amount);
			break;
		}
	}
	Arsenal[ActiveWeapon]->UpdateAmmoString();
	return Success;
}

bool ASCMPlayerCharacter::PickupWeapon(WeaponType WeaponType, int Amount)
{
	
	if (UnlockedGuns[WeaponType] == false)
	{
		UnlockedGuns[WeaponType] = true;
		return false;	// weapon was not unlocked previously 
	}
	else
		return true;	// weapon already unlocked

}


void ASCMPlayerCharacter::ActivateStim()
{

	if (StimActive)
	{
		// stim already active just clear timer and reset
		GetWorldTimerManager().ClearTimer(StimTimerHandle);
		GetWorldTimerManager().SetTimer(StimTimerHandle, this, &ASCMPlayerCharacter::DisableStim, StimLength, false);
		return;
	}

	StimActive = true;
	GetWorldTimerManager().SetTimer(StimTimerHandle, this, &ASCMPlayerCharacter::DisableStim, StimLength, false);

	for (ASCMWeapon* Gun : Arsenal)
	{
		if (Gun)
		{
			Gun->SetStimMode();
		}
	}

	UCharacterMovementComponent* CharMovementComp = GetCharacterMovement();
	float MaxSpeed = CharMovementComp->MaxWalkSpeed;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::SanitizeFloat(MaxSpeed));
	CharMovementComp->MaxWalkSpeed = MaxSpeed *= 1.5;
}

void ASCMPlayerCharacter::DisableStim()
{
	GetWorldTimerManager().ClearTimer(StimTimerHandle);
	StimActive = false;
	
	for (ASCMWeapon* Gun : Arsenal)
	{
		if (Gun) 
		{
			Gun->SetRegularMode();
		}
	}

	UCharacterMovementComponent* CharMovementComp = GetCharacterMovement();
	float MaxSpeed = CharMovementComp->MaxWalkSpeed;
	CharMovementComp->MaxWalkSpeed = MaxSpeed /= 1.5f;
}

void ASCMPlayerCharacter::CamZoomIn()
{
	FPSCameraComponent->SetFieldOfView(20.0f);
	MouseSense /= 4.0f;
	FPSMeshRefresh->SetOwnerNoSee(true);
}

void ASCMPlayerCharacter::CamZoomOut()
{
	FPSCameraComponent->SetFieldOfView(90.0f);
	MouseSense *= 4.0f;
	FPSMeshRefresh->SetOwnerNoSee(false);
}

void ASCMPlayerCharacter::TurnOnNightvision_Implementation()
{
}

void ASCMPlayerCharacter::TurnOffNightvision_Implementation()
{
}

void ASCMPlayerCharacter::Nightvision()
{
	AHSSniper* IsSniper = Cast<AHSSniper>(Arsenal[ActiveWeapon]);

	if (IsSniper)
	{
		if (IsSniper->GetIsScopedIn())
		{
			if (IsSniper->GetIsNightvisionOn())
			{
				IsSniper->SetIsNightvisionOn(false);
				TurnOffNightvision();
			}
			else
			{
				IsSniper->SetIsNightvisionOn(true);
				TurnOnNightvision();
				
				if (NightvisionOnSFX)
				{
					UGameplayStatics::PlaySoundAtLocation(GetWorld(), NightvisionOnSFX, this->GetActorLocation());
				}
			}
		}
	}
}


void ASCMPlayerCharacter::GiveKey(KeyType Key)
{
	KeyArray.Insert(true, Key);
	if (PlayerController)
	{
		PlayerController->PrintKeycard(Key);
	}
}
