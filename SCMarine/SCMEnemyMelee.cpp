// Fill out your copyright notice in the Description page of Project Settings.

#include "SCMEnemyMelee.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

ASCMEnemyMelee::ASCMEnemyMelee()
{
	// Can't define them in cpp because they won't attach to skeletal mesh sockets for some reason...?
	// Init Attack Collision Components
	//AttackCollisionLeft = CreateDefaultSubobject<UCapsuleComponent>(TEXT("AttackCollisionLeft"));
	//AttackCollisionLeft->SetupAttachment(CharacterMesh);

	//AttackCollisionRight = CreateDefaultSubobject<UCapsuleComponent>(TEXT("AttackCollisionRight"));
	//AttackCollisionRight->AttachToComponent(CharacterMesh, FAttachmentTransformRules::KeepRelativeTransform, FName("RightAttackSocket"));

}


void ASCMEnemyMelee::MeleeAttack(AActor* Target, UPrimitiveComponent* MeleeHitbox)
{
	if (!bCanDealDamage) { return; }

	UGameplayStatics::PlaySoundAtLocation(this, MeleeAttackSound, GetActorLocation(), 1.0f);
	UGameplayStatics::ApplyDamage(Target, MeleeAttackDamage, GetInstigatorController(), this, nullptr);
	bCanDealDamage = false;

	if (MeleeHitbox)
	{
		FVector LaunchDirection = MeleeHitbox->GetForwardVector();
		LaunchDirection = LaunchDirection * -250.0f; // This is how my bp was set up, don't remember why lol

		ACharacter* Character = Cast<ACharacter>(Target);
		if (Character)
		{
			Character->LaunchCharacter(LaunchDirection, false, false);
		}
	}

}