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
	SetCanBeDamaged(false);
	bCanDealDamage = false;

	//Disable "body"
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
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
			AIController->DeactivatePerception();
			AIController->UnPossess();
		}
		else
		{
			//Controller->UnPossess();
		}
	}
	SetLifeSpan(10.0f);

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
	// Do nothing
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



