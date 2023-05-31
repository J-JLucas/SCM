// Fill out your copyright notice in the Description page of Project Settings.


#include "HSShotgun.h"
#include "Kismet/GameplayStatics.h"
#include "SCMarine/SCMEnemy.h"


AHSShotgun::AHSShotgun()
{
	SetGunshotSFX(GunshotPath);
}

void AHSShotgun::BeginPlay()
{
	Super::BeginPlay();
	SetDamageAmount(10.0f);
}

void AHSShotgun::PrimaryFire(APlayerController* PController, AActor* PossessedActor)
{

	FVector CameraLocation;
	FRotator CameraRotation;
	FHitResult Hit;
	UWorld* World = PossessedActor->GetWorld();
	int32 ShotCount = 10;

	APlayerController* PlayerController = Cast<APlayerController>
		(UGameplayStatics::GetPlayerController(GetWorld(), 0));;
	PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

	PlayGunshotSFX(PossessedActor);
	// fire ShotCount Pellets
	for (int32 i = 0; i < ShotCount; i++)
	{
		float Spread = 17.0f;
		float SpreadValue = FMath::RandRange(0.0f, Spread);

		FVector Start = CameraLocation;
		FVector ShootDir = CameraRotation.Vector();

		// Generate random angles for cone spread
		float ConeHalfAngle = FMath::DegreesToRadians(SpreadValue * 0.5f);
		float RandomPitch = FMath::FRandRange(-ConeHalfAngle, ConeHalfAngle);
		float RandomYaw = FMath::FRandRange(-ConeHalfAngle, ConeHalfAngle);

		// Apply random pitch and yaw to shoot direction
		FRotator ShootRot = FRotator(ShootDir.Rotation().Pitch + FMath::RadiansToDegrees(RandomPitch), ShootDir.Rotation().Yaw + FMath::RadiansToDegrees(RandomYaw), 0.0f);
		FVector SpreadDirection = ShootRot.Vector();

		FVector End = Start + (SpreadDirection * Range);

		
		//FVector End = Start + (CameraRotation.Vector() * Range) + SpreadDirection;

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
				UGameplayStatics::ApplyPointDamage(Enemy, Damage, HitFromDirection, Hit, PlayerController, PossessedActor, nullptr);

			}
		}
	}

}