// Fill out your copyright notice in the Description page of Project Settings.


#include "SCMEnemy.h"
#include "HealthComponent.h"
//#include "Perception/PawnSensingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ASCMEnemy::ASCMEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//CharacterMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("EnemyCharacterMesh"));
	//check(CharacterMesh != nullptr);
	//CharacterMesh->SetupAttachment(GetRootComponent());
	//CharacterMesh->bCastDynamicShadow = false;

	// Init AI senses
	//PawnSenseComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
	//PawnSenseComp->SetPeripheralVisionAngle(50.0f);
	//PawnSenseComp->SetSensingInterval(0.25f);

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
	//SetCanBeDamaged(false);
	bCanDealDamage = false;
	//GetCharacterMovement()->StopMovementImmediately();
	//GetMesh()->GetAnimInstance()->

	if (Controller)
	{
		Controller->UnPossess();
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



