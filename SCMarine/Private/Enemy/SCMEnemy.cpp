// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/SCMEnemy.h"
#include "HealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AI/SCMAIController.h"

// Sets default values
ASCMEnemy::ASCMEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//CharacterMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("EnemyCharacterMesh"));
	//check(CharacterMesh != nullptr);
	//CharacterMesh->SetupAttachment(GetRootComponent());
	//CharacterMesh->bCastDynamicShadow = false;

	// Init Health Component
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	HealthComponent->SetMaxHealth(DefaultHealth);
}


// Called when the game starts or when spawned
void ASCMEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void ASCMEnemy::OnDeath_Implementation()
{
	SetLifeSpan(10.0f);
	SetCanBeDamaged(false);
	bCanDealDamage = false;

	//Disable "body"
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel4, ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCanEverAffectNavigation(false);

	// Disable any event animations eg attack
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		if (AnimInstance->IsAnyMontagePlaying()) 
		{
			AnimInstance->Montage_Stop(0.0f, AnimInstance->GetCurrentActiveMontage());
		}
	}

	if (Controller)
	{
		ASCMAIController* AIController = Cast<ASCMAIController>(Controller);
		if (AIController)
		{
			//AIController->DeactivatePerception();
			//AIController->UnPossess();
		}
		else
		{
			//Controller->UnPossess();
		}
	}
}

// Called every frame
void ASCMEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASCMEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void ASCMEnemy::OnTakeDamage_Implementation()
{
	/*
	ASCMAIController* AIController = Cast<ASCMAIController>(Controller);
	if (AIController)
	{
		AIController->HandleTakeDamage();
	}
	*/
}

void ASCMEnemy::SwitchToAttackSpeed()
{
	GetCharacterMovement()->MaxWalkSpeed = MaxSpeed;
	return;
}

void ASCMEnemy::SwitchToWalkSpeed()
{
	GetCharacterMovement()->MaxWalkSpeed = IdleSpeed;
	return;
}

void ASCMEnemy::PlayAlertBark()
{
	UGameplayStatics::PlaySoundAtLocation(this, AlertSound, GetActorLocation());
}


FVector ASCMEnemy::GetPlayerLocation() const
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		APawn* PlayerChar = PlayerController->GetPawn();
		if (PlayerChar)
		{
			return PlayerChar->GetActorLocation();
		}
	}
	return FVector();
}


FRotator ASCMEnemy::FindLookAtRotation(const FVector& Start, const FVector& Target)
{
	return FRotationMatrix::MakeFromX(Target - Start).Rotator();
}
