// Fill out your copyright notice in the Description page of Project Settings.

#include "SCMEnemyMelee.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "SCMPlayerCharacter.h"

ASCMEnemyMelee::ASCMEnemyMelee()
{
	// Can't define them in cpp because they won't attach to skeletal mesh sockets for some reason...?
	// Init Attack Collision Components
	//AttackCollisionLeft = CreateDefaultSubobject<UCapsuleComponent>(TEXT("AttackCollisionLeft"));
	//AttackCollisionLeft->SetupAttachment(CharacterMesh);

	//AttackCollisionRight = CreateDefaultSubobject<UCapsuleComponent>(TEXT("AttackCollisionRight"));
	//AttackCollisionRight->AttachToComponent(CharacterMesh, FAttachmentTransformRules::KeepRelativeTransform, FName("RightAttackSocket"));

}

// Start the melee attack procedure
void ASCMEnemyMelee::MeleeAttack()
{
	bCanDealDamage = true;
	
	// Select a random attack montage to play.
	UAnimMontage* SelectedMontage = ChooseAttackMontage();
	if (SelectedMontage)
	{
		PlayAnimMontage(SelectedMontage);
	}
}

// Chooses a random attack animation to play
// Populate the array in the bp inside the editor
UAnimMontage* ASCMEnemyMelee::ChooseAttackMontage()
{
	if (AttackMontages.Num() == 0) { return nullptr; }

	int32 MontageIndex = FMath::RandRange(0, AttackMontages.Num() - 1);
	return AttackMontages.IsValidIndex(MontageIndex) ? AttackMontages[MontageIndex] : nullptr;
}


// Deal Damage if allowed
void ASCMEnemyMelee::DealMeleeDamage(AActor* Target, UPrimitiveComponent* MeleeHitbox)
{
	// No friendly fire... yet... 
	ASCMPlayerCharacter* SCMPlayerCharacter = Cast<ASCMPlayerCharacter>(Target);
	if (!SCMPlayerCharacter) { return; }
	if (!bCanDealDamage) { return; }

	UGameplayStatics::PlaySoundAtLocation(this, MeleeAttackSound, GetActorLocation(), 1.0f);
	UGameplayStatics::ApplyDamage(Target, MeleeAttackDamage, GetInstigatorController(), this, nullptr);
	bCanDealDamage = false;

	if (MeleeHitbox)
	{
		// knock the character back
		FVector LaunchDirection = MeleeHitbox->GetForwardVector();
		LaunchDirection = LaunchDirection * MeleeForce; 
		LaunchDirection.Z += ForceHeight;
		ACharacter* Character = Cast<ACharacter>(Target);
		if (Character)
		{
			Character->LaunchCharacter(LaunchDirection, false, false);
		}
	}
}