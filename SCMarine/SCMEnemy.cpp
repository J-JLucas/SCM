// Fill out your copyright notice in the Description page of Project Settings.


#include "SCMEnemy.h"
#include "HealthComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ASCMEnemy::ASCMEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//EnemyMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("EnemyMeshComponent"));
	//check(EnemyMeshComponent != nullptr);
	//SetRootComponent(EnemyMeshComponent);

	// Load the skeletal mesh asset
	//EnemyMesh = LoadObject<USkeletalMesh>(nullptr, TEXT("'/Game/Models/Units/Zergling/zergling_model.zergling_model'"));

	// Set the skeletal mesh on the component
	//EnemyMeshComponent->SetSkeletalMesh(EnemyMesh);

	// Init AI senses
	//PawnSenseComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
	//PawnSenseComp->SetPeripheralVisionAngle(50.0f);
	//PawnSenseComp->SetSensingInterval(0.25f);


	// Init Health Component
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	HealthComponent->SetMaxHealth(DefaultHealth);

	// Set Death Animation
	//static ConstructorHelpers::FObjectFinder<UAnimSequence> anim(TEXT("AnimSequence'/Script/Engine.AnimSequence'/Game/Models/Units/Zergling/Animations/Death/ZerglingDeath1.ZerglingDeath1''"));
	//DeathAnimation = anim.Object;

	// Init Attack Collision Components
	//AttackCollisionLeft = CreateDefaultSubobject<UCapsuleComponent>(TEXT("AttackCollisionLeft"));
	//AttackCollisionLeft->AttachToComponent(EnemyMeshComponent, FAttachmentTransformRules::KeepRelativeTransform, FName("LeftSocket"));
	//AttackCollisionLeft->SetupAttachment(EnemyMeshComponent, FName("LeftSocket"));
	
	//AttackCollisionRight = CreateDefaultSubobject<UCapsuleComponent>(TEXT("AttackCollisionRight"));
	
	//AttackCollisionRight->AttachToComponent(EnemyMeshComponent, FAttachmentTransformRules::KeepRelativeTransform, FName("RightSocket"));

}


// Called when the game starts or when spawned
void ASCMEnemy::BeginPlay()
{
	Super::BeginPlay();

}

void ASCMEnemy::OnDeath_Implementation()
{
	//GetMesh()->PlayAnimation(DeathAnimation, false);
	SetCanBeDamaged(false);
	//Destroy();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Actor Destroyed");

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

void ASCMEnemy::MeleeAttack()
{
	// Attack logic goes here
	
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



