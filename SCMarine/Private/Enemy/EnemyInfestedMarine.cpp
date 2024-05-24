// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyInfestedMarine.h"
#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SCMPlayerCharacter.h"
#include "PhysicsEngine/RadialForceComponent.h"

AEnemyInfestedMarine::AEnemyInfestedMarine()
{
	float MaxHealth = (200.0f);
	// Init Health Component
	HealthComponent->SetMaxHealth(MaxHealth);
	
	// Init radial force component
	RadialForce = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForce"));
}


// suicide bomb explosion
void AEnemyInfestedMarine::MeleeAttack()
{
	// Select a random attack montage to play.
	UAnimMontage* SelectedMontage = ChooseAttackMontage(MeleeAttackMontages);
	if (SelectedMontage)
	{
		PlayAnimMontage(SelectedMontage);
	}
	GetWorldTimerManager().SetTimer(ExplosionTimer, this, &AEnemyInfestedMarine::Explode, CountDownTime, false);
}

void AEnemyInfestedMarine::Explode()
{
	FVector SpawnLocation = GetActorLocation();

	// Kill self
	HealthComponent->TakeDamage(this, 9999.0f, nullptr, GetController(), this);

	// Spawn Explosion Effect
	UGameplayStatics::SpawnEmitterAtLocation(this, ExplosionEffect, SpawnLocation + FVector(0.0f, 0.0f, 40.0f),
		FRotator::ZeroRotator, FVector(2.0f, 2.0f, 2.0f), true, EPSCPoolMethod::AutoRelease);

	// Deal Explosive Radial Damage
	UGameplayStatics::ApplyRadialDamage(GetWorld(), ExplosionDamage, SpawnLocation, ExplosionRadius, nullptr,
		TArray<AActor*>(), this, GetInstigatorController(),
		false, ECollisionChannel::ECC_Visibility
	);

	DrawDebugSphere(GetWorld(), SpawnLocation + FVector(0.0f, 0.0f, -40.0f), ExplosionRadius, 8, FColor::Red, false, 1.0f);

	// Apply knockback force to all in explosion radius
	RadialForce->SetRelativeLocation(SpawnLocation + FVector(0.0f, 0.0f, -40.0f));
	RadialForce->Radius = ExplosionRadius;
	RadialForce->ImpulseStrength = ExplosionStrength;
	RadialForce->ForceStrength = ExplosionStrength;
	RadialForce->bImpulseVelChange = true;
	RadialForce->bIgnoreOwningActor = true;
	RadialForce->FireImpulse();

	Destroy();
}


// Hitscan burst rifle shot
void AEnemyInfestedMarine::RangedAttack()
{
	// Play attack montage
	Super::RangedAttack();

	FVector ForwardVector = GetActorForwardVector();
	float SpawnDistance = 200.f;
	float Range = 5000.0f;
	float ShotCount = 3.0f;

	FVector SpawnLocation = GetActorLocation() + (ForwardVector * SpawnDistance);	//line trace starts 200 points forward
	FRotator SpawnRotation = FindLookAtRotation(GetActorLocation() + FVector(0.0f, 0.0f, 40.0f), GetPlayerLocation());
	UWorld* World = GetWorld();
	FHitResult Hit;
	
	// Calculate a random deviation within a maximum angle (Algie from ChatGPT)
	float MaxPitchDeviation = 3.0f; // Adjust this value to control the maximum pitch(up/down) angle
	float MaxYawDeviation = 3.0f;   // Adjust this value to control the maximum yaw(left/right) deviation
	
	for (int32 i = 0; i < ShotCount; i++) {

		FRotator RandomRotation = FRotator(FMath::RandRange(-MaxPitchDeviation, MaxPitchDeviation), FMath::RandRange(-MaxYawDeviation, MaxYawDeviation), 0.0f);
		SpawnRotation += RandomRotation;

		FVector Start = SpawnLocation;
		FVector End = Start + (SpawnRotation.Vector() * Range);

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
				Player->LaunchCharacter(-HitFromDirection * ImpulseStrength, true, true);
			}
		}
	}
}
