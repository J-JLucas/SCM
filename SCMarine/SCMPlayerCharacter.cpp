// Fill out your copyright notice in the Description page of Project Settings.


#include "SCMPlayerCharacter.h"
#include "SCMarinePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "HealthComponent.h"
#include "SCMEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/SkeletalMesh.h"
#include "Public/SCMWeapon.h"
#include "Public/HSPistol.h"
#include "Public/HSShotgun.h"
#include "Public/HSRifle.h"
#include "Public/HSSniper.h"
#include "Public/PRocketLauncher.h"
#include "Public/PFlameThrower.h"
#include "SCMarine/SCMarinePlayerController.h"

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
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	check(FPSMesh != nullptr);

	// Only owning player can see mesh
	FPSMesh->SetOnlyOwnerSee(true);

	//Attach the FPS mesh to the FPS camera
	FPSMesh->SetupAttachment(FPSCameraComponent);

	// Disable environmental shadows to preserve the illusion of having a single mesh
	// (disables the arms' shadow, not the full body shadow that other players can see
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;

	// Hide 3rd person mesh from FPS Cam
	GetMesh()->SetOwnerNoSee(true);

	// Init Health Component
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	HealthComponent->SetMaxHealth(MaxHealth);

	// Safe initialization, if you create objects here it's too slow and they don't work
	// gotta do it in BeginPlay()
	PController = nullptr;
	PossessedActor = nullptr;

	// Init Weapon objects
	Arsenal.Init(nullptr, 8);

	wMelee = nullptr;

	wPistolPlayer = CreateDefaultSubobject<AHSPistol>(TEXT("PlayerPistol"));

	wShotgunPlayer = CreateDefaultSubobject<AHSShotgun>(TEXT("PlayerShotgun"));

	wRiflePlayer = CreateDefaultSubobject<AHSRifle>(TEXT("PlayerRifle"));

	wSniperPlayer = CreateDefaultSubobject<AHSSniper>(TEXT("PlayerSniper"));

	wRocketLPlayer = CreateDefaultSubobject<APRocketLauncher>(TEXT("PlayerRocketLauncher"));

	wFThrowerPlayer = CreateDefaultSubobject<APFlameThrower>(TEXT("PlayerFlameThrower"));
		
}

void ASCMPlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	BeginPlay();
}

// Called when the game starts or when spawned
void ASCMPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(IC_PlayerChar, 1);
		}
	}
	// Initialize Weapons ... need to manually BeginPlay() because
	// they aren't instantiated in the world?
	// Load meshes and insert into Arsenal TArray
	wPistolPlayer->BeginPlay();
	Arsenal.Insert(wPistolPlayer, WeaponType::Pistol);
	PistolMesh = LoadObject<USkeletalMesh>(nullptr, *PistolMeshPath);
	
	wShotgunPlayer->BeginPlay();
	Arsenal.Insert(wShotgunPlayer, WeaponType::Shotgun);
	ShotgunMesh = LoadObject<USkeletalMesh>(nullptr, *ShotgunMeshPath);

	wRiflePlayer->BeginPlay();
	Arsenal.Insert(wRiflePlayer, WeaponType::Rifle);
	RifleMesh = LoadObject<USkeletalMesh>(nullptr, *RifleMeshPath);

	wSniperPlayer->BeginPlay();
	Arsenal.Insert(wSniperPlayer, WeaponType::Sniper);
	SniperMesh = LoadObject<USkeletalMesh>(nullptr, *SniperMeshPath);
	
	wRocketLPlayer->BeginPlay();
	Arsenal.Insert(wRocketLPlayer, WeaponType::RocketL);
	RocketLMesh = LoadObject<USkeletalMesh>(nullptr, *RocketLMeshPath);

	wFThrowerPlayer->BeginPlay();
	Arsenal.Insert(wFThrowerPlayer, WeaponType::FThrower);
	FThrowerMesh = LoadObject<USkeletalMesh>(nullptr, *FThrowerMeshPath);

	// Default Weapon
	SwitchWeapon(WeaponType::Rifle);
	
	// Initialize PController
	PController = GetWorld()->GetFirstPlayerController();

	// Initialize PossessedActor
	PossessedActor = this;
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

		//Jump
		EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &ASCMPlayerCharacter::Jump);
		EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Completed, this, &ASCMPlayerCharacter::StopJumping);
	
		//Switch Weapons
		EnhancedInputComponent->BindAction(IA_SwitchSpecial, ETriggerEvent::Triggered, this, &ASCMPlayerCharacter::SwitchWeapon, WeaponType::Special);
		EnhancedInputComponent->BindAction(IA_SwitchPistol, ETriggerEvent::Triggered, this, &ASCMPlayerCharacter::SwitchWeapon, WeaponType::Pistol);
		EnhancedInputComponent->BindAction(IA_SwitchShotgun, ETriggerEvent::Triggered, this, &ASCMPlayerCharacter::SwitchWeapon, WeaponType::Shotgun);
		EnhancedInputComponent->BindAction(IA_SwitchRifle, ETriggerEvent::Triggered, this, &ASCMPlayerCharacter::SwitchWeapon, WeaponType::Rifle);
		EnhancedInputComponent->BindAction(IA_SwitchSniper, ETriggerEvent::Triggered, this, &ASCMPlayerCharacter::SwitchWeapon, WeaponType::Sniper);
		EnhancedInputComponent->BindAction(IA_SwitchRL, ETriggerEvent::Triggered, this, &ASCMPlayerCharacter::SwitchWeapon, WeaponType::RocketL);
		EnhancedInputComponent->BindAction(IA_SwitchFL, ETriggerEvent::Triggered, this, &ASCMPlayerCharacter::SwitchWeapon, WeaponType::FThrower);
	
	}
}

void ASCMPlayerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ASCMPlayerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ASCMPlayerCharacter::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Fire input received!"));
	
	// Check if PController and PossessedActor are valid
	check(PController != nullptr);
	check(PossessedActor != nullptr);

	switch (ActiveWeapon)
	{
		case(WeaponType::Special):
		{
			UE_LOG(LogTemp, Warning, TEXT("Fired Special"));
			break;
		}
		case(WeaponType::Pistol):
		{
			Arsenal[WeaponType::Pistol]->PrimaryFire(PController, PossessedActor);
			UE_LOG(LogTemp, Warning, TEXT("Fired Pistol"));
			break;
		}
		case(WeaponType::Shotgun):
		{
			Arsenal[WeaponType::Shotgun]->PrimaryFire(PController, PossessedActor);
			UE_LOG(LogTemp, Warning, TEXT("Fired Shotgun"));
			break;
		}
		case(WeaponType::Rifle):
		{
			Arsenal[WeaponType::Rifle]->PrimaryFire(PController, PossessedActor);
			UE_LOG(LogTemp, Warning, TEXT("Fired GaussRifle"));
			break;
		}
		case(WeaponType::Sniper):
		{
			Arsenal[WeaponType::Sniper]->PrimaryFire(PController, PossessedActor);
			UE_LOG(LogTemp, Warning, TEXT("Fired SniperRifle"));
			break;
		}
		case(WeaponType::RocketL):
		{
			Arsenal[WeaponType::RocketL]->PrimaryFire(PController, PossessedActor);
			UE_LOG(LogTemp, Warning, TEXT("Fired RocketLauncher"));
			break;
		}
		case(WeaponType::FThrower):
		{	
			Arsenal[WeaponType::FThrower]->PrimaryFire(PController, PossessedActor);
			UE_LOG(LogTemp, Warning, TEXT("Fired FlameThrower"));
			break;
		}
	}
}

void ASCMPlayerCharacter::SwitchWeapon(WeaponType NewWeapon)
{
	ActiveWeapon = NewWeapon;
	FTransform ResetTransform(FQuat::Identity, FVector::ZeroVector, FVector::OneVector);
	FPSMesh->SetRelativeTransform(ResetTransform);

	switch (NewWeapon) 
	{
		case(WeaponType::Special):
		{
			UE_LOG(LogTemp, Warning, TEXT("Switched To Special"));
			break;
		}
		case(WeaponType::Pistol):
		{
			FPSMesh->SetSkeletalMesh(PistolMesh);
			FPSMesh->AddRelativeLocation(FVector(74.0f, 60.0f, -51.0f));
			FPSMesh->AddRelativeRotation(FRotator(0.0f, -172.0f, 0.0f));
			UE_LOG(LogTemp, Warning, TEXT("Switched To Pistol"));
			break;
		}
		case(WeaponType::Shotgun):
		{
			FPSMesh->SetSkeletalMesh(ShotgunMesh);
			FPSMesh->AddRelativeLocation(FVector(46.0f, -20.0f, -98.0f));
			FPSMesh->AddRelativeRotation(FRotator(4.0f, -86.0f,-50.0f));
			UE_LOG(LogTemp, Warning, TEXT("Switched To Shotgun"));
			break;
		}
		case(WeaponType::Rifle):
		{
			FPSMesh->SetSkeletalMesh(RifleMesh);
			FPSMesh->AddRelativeLocation(FVector(2.0f, 48.0f, -58.0f));
			FPSMesh->AddRelativeRotation(FRotator(0.0f, -88.0f, -1.0f));
			UE_LOG(LogTemp, Warning, TEXT("Switched To GaussRifle"));
			break;
		}
		case(WeaponType::Sniper):
		{
			FPSMesh->SetSkeletalMesh(SniperMesh);
			FPSMesh->AddRelativeLocation(FVector(175.0f, 58.0f, -100.0f));
			FPSMesh->AddRelativeRotation(FRotator(-2.25f, -85.0, 4.5f));
			UE_LOG(LogTemp, Warning, TEXT("Switched To SniperRifle"));
			break;
		}
		case(WeaponType::RocketL):
		{
			FPSMesh->SetSkeletalMesh(RocketLMesh);
			FPSMesh->AddRelativeLocation(FVector(180.0f, 29.0f, -128.0f));
			FPSMesh->AddRelativeRotation(FRotator(-85.0f, -73.0, 238.0f));
			UE_LOG(LogTemp, Warning, TEXT("Switched To RocketLauncher"));
			break;
		}
		case(WeaponType::FThrower):
		{
			FPSMesh->SetSkeletalMesh(FThrowerMesh);
			FPSMesh->AddRelativeLocation(FVector(21.0f, 22.0f, -37.0f));
			FPSMesh->AddRelativeRotation(FRotator(-3.0f, -0.5, 0.0f));
			UE_LOG(LogTemp, Warning, TEXT("Switched To FlameThrower"));
			break;
		}
	}
}

void ASCMPlayerCharacter::OnDeath_Implementation()
{
	DisableInput(PController);
	FPSMesh->SetOwnerNoSee(true);
	SetCanBeDamaged(false);

	//Destroy();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "PlayerCharacter Destroyed");
}

void ASCMPlayerCharacter::OnTakeDamage_Implementation()
{
	ASCMarinePlayerController* PlayerController =
		Cast<ASCMarinePlayerController>(GetController());

	if (PlayerController)
	{
		PlayerController->UpdateHealthPercent(HealthComponent->GetHealthPercent());
	}

}