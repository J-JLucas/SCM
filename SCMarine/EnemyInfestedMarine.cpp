// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyInfestedMarine.h"
#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SCMPlayerCharacter.h"

AEnemyInfestedMarine::AEnemyInfestedMarine()
{
	float MaxHealth = (200.0f);
	// Init Health Component
	HealthComponent->SetMaxHealth(MaxHealth);

}

void AEnemyInfestedMarine::IMRangedAttack()
{
	float SpawnDistance = 200.f;
	float Range = 5000.0f;
	float ShotCount = 3.0f;
	FVector ForwardVector = GetActorForwardVector();
	FVector SpawnLocation = GetActorLocation() + (ForwardVector * SpawnDistance);	//line trace starts 200 points forward
	FRotator SpawnRotation = GetActorRotation();
	UWorld* World = GetWorld();
	FHitResult Hit;
	

	// Calculate a random deviation within a maximum angle (Algie from ChatGPT)
	float MaxPitchDeviation = 3.0f; // Adjust this value to control the maximum pitch(up/down) angle
	float MaxYawDeviation = 3.0f;   // Adjust this value to control the maximum yaw(left/right) deviation

	for (int32 i = 0; i < ShotCount; i++) {

		FRotator RandomRotation = FRotator(FMath::RandRange(-MaxPitchDeviation, MaxPitchDeviation), FMath::RandRange(-MaxYawDeviation, MaxYawDeviation), 0.0f);
		RandomRotation += SpawnRotation;

		FVector Start = SpawnLocation;
		FVector End = Start + (RandomRotation.Vector() * Range);

		FCollisionQueryParams TraceParams;
		TraceParams.AddIgnoredActor(this);		// don't shoot self LOL

		// BurstFire Trace
		bool bHit = World->LineTraceSingleByChannel(Hit, Start, End, ECC_Pawn, TraceParams);
		DrawDebugLine(World, Start, End, FColor::Purple, false, 5.0f);

		if (bHit)
		{
			DrawDebugBox(World, Hit.ImpactPoint, FVector(5, 5, 5), FColor::Emerald, false, 5.0f);

			ASCMPlayerCharacter* Player = Cast<ASCMPlayerCharacter>(Hit.GetActor());
			if (Player)
			{
				float Damage = 5.0f;
				FVector HitFromDirection = (Start - End).GetSafeNormal();
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, "Hit Player");
				UGameplayStatics::ApplyPointDamage(Player, Damage, HitFromDirection, Hit, GetController(), this, nullptr);

			}
		}
	}
}
