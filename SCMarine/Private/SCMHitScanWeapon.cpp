// Fill out your copyright notice in the Description page of Project Settings.


#include "SCMHitScanWeapon.h"
#include "SCMarine/SCMEnemy.h"
#include "SCMarine/SCMPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

void ASCMHitScanWeapon::TraceForward(APlayerController* PController, AActor* PossessedActor)
{
	
	FVector CameraLocation;
	FRotator CameraRotation;
	FHitResult Hit;
	UWorld* World = PossessedActor->GetWorld();

	APlayerController* PlayerController = Cast<APlayerController>
		(UGameplayStatics::GetPlayerController(GetWorld(), 0));;
	PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

	FVector Start = CameraLocation;
	FVector End = Start + (CameraRotation.Vector() * Range);

	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(PossessedActor);		// don't shoot self LOL
	bool bHit = World->LineTraceSingleByChannel(Hit, Start, End, ECC_Pawn, TraceParams);

	DrawDebugLine(World, Start, End, FColor::Purple, false, 5.0f);
	
	if (bHit)
	{
		DrawDebugBox(World, Hit.ImpactPoint, FVector(5, 5, 5), FColor::Emerald, false, 5.0f);

		ASCMEnemy* Enemy = Cast<ASCMEnemy>(Hit.GetActor());
		if (Enemy)
		{
			float Damage = GetDamageAmount();
			FVector HitFromDirection = (Start - End).GetSafeNormal();
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, "Hit Enemy");
			UGameplayStatics::ApplyPointDamage(Enemy, Damage,HitFromDirection, Hit, PlayerController, PossessedActor, nullptr);
			
		}
	}
}

void ASCMHitScanWeapon::PrimaryFire(APlayerController* PController, AActor* PossessedActor)
{
	if ((!bIsFiring) && (CurrentMag > 0) && (!bIsReloading))
	{
		Super::PrimaryFire(PController, PossessedActor);
		StartFiring();
		PlayFireAnimation(PossessedActor);
		PlayGunshotSFX(PossessedActor);
		TraceForward(PController, PossessedActor);
	}
}

