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
#include "Public/HSRifle.h"
#include "SCMarine/SCMarinePlayerController.h"

// Sets default values
ASCMPlayerCharacter::ASCMPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
	float MaxHealth = 100.0f;
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	HealthComponent->SetMaxHealth(MaxHealth);

	// Safe initialization, if you create objects here it's too slow and they don't work
	// gotta do it in BeginPlay()
	PController = nullptr;
	PossessedActor = nullptr;
	Rifle = nullptr;

	// Get Reference to PC's Pawn
	//PossessedActor = this;

	//Rifle = CreateDefaultSubobject<AHSRifle>(TEXT("Rifle"));
	//if (Rifle == nullptr) {UE_LOG(LogTemp, Warning, TEXT("Rifle  constructor!"));}
	//else { UE_LOG(LogTemp, Warning, TEXT("Rifle Init Successful!")) 
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

	// Initialize Rifle
	Rifle = NewObject<AHSRifle>(this);
	// Perform any additional initialization or configuration for Rifle if needed

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
	}
}

void ASCMPlayerCharacter::Look(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Look input received!"));
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ASCMPlayerCharacter::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Fire input received!"));
	if (Rifle)
	{
		// Check if PController and PossessedActor are valid
		check(PController != nullptr);
		check(PossessedActor != nullptr);

		Rifle->PrimaryFire(PController, PossessedActor);
	}
	else
	{
		// Output a log message if Rifle is null
		UE_LOG(LogTemp, Warning, TEXT("Rifle is null!"));
	}
	
	if (PController) { UE_LOG(LogTemp, Warning, TEXT("PController is good!")); }
	else { UE_LOG(LogTemp, Warning, TEXT("PController is null!")); }

	if (PossessedActor) { UE_LOG(LogTemp, Warning, TEXT("PActor is good!")); }
	else { UE_LOG(LogTemp, Warning, TEXT("PActor is null!")); }

}

void ASCMPlayerCharacter::OnDeath_Implementation()
{
	Destroy();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "PlayerCharacter Destroyed");
}

void ASCMPlayerCharacter::Move(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Move input received!"));
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
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