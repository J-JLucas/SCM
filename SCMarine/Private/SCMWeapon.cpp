// Fill out your copyright notice in the Description page of Project Settings.


#include "SCMWeapon.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "SCMarine/SCMarinePlayerController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASCMWeapon::ASCMWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ASCMWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASCMWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASCMWeapon::PrimaryFire(APlayerController* PController, AActor* PossessedActor)
{
	CurrentMag--;
	UpdateMagString();
}

void ASCMWeapon::AltFire()
{
	// Reserved for future use
}

void ASCMWeapon::ReloadWeapon()
{

	if ((CurrentAmmo == 0) ||(CurrentMag == MaxMag)) { return; }
	StartReloading();
	return;
}


void ASCMWeapon::SetGunshotSFX(FString Path)
{
	// Init Gunshot SoundFX
	// Find the sound wave object **I FUCKING LOVE YOU BING CHAN**

	USoundWave* SoundWave = Cast<USoundWave>(StaticLoadObject(USoundWave::StaticClass(), nullptr, *Path));
	if (SoundWave == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load sound wave"));
	}
	else
	{
		// Set the Gunshot variable to the loaded sound wave object
		Gunshot = SoundWave;
	}
}

void ASCMWeapon::StartFiring()
{
	bIsFiring = true;
	GetWorldTimerManager().SetTimer(FireHandle, this, &ASCMWeapon::StopFiring, FireRate, false);
	return;
}

void ASCMWeapon::StopFiring()
{
	GetWorldTimerManager().ClearTimer(FireHandle);
	bIsFiring = false;
	return;
}

void ASCMWeapon::StartReloading()
{
	bIsReloading = true;
	GetWorldTimerManager().SetTimer(ReloadHandle, this, &ASCMWeapon::StopReloading, ReloadRate, false);
	
}

void ASCMWeapon::StopReloading()
{
	GetWorldTimerManager().ClearTimer(ReloadHandle);
	bIsReloading = false;

	float BulletsNeeded = MaxMag - CurrentMag;

	if (BulletsNeeded > CurrentAmmo)
	{
		CurrentMag += CurrentAmmo;
		CurrentAmmo = 0.0f;

	}
	else
	{
		CurrentAmmo -= BulletsNeeded;
		CurrentMag = MaxMag;

	}

	UpdateMagString();
	UpdateAmmoString();
	return;
}

void ASCMWeapon::SetDamageAmount(float Damage)
{
	DamageAmount = Damage;
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Set Damage Value."));
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::SanitizeFloat(Damage));
}

void ASCMWeapon::SetRangeAmount(float RangeValue)
{
	Range = RangeValue;
}

void ASCMWeapon::UpdateMagString()
{
	ASCMarinePlayerController* PlayerController =
		Cast<ASCMarinePlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	if (PlayerController)
	{
		PlayerController->UpdateMagCount(CurrentMag);
	}
	return;
}
void ASCMWeapon::UpdateAmmoString()
{
	ASCMarinePlayerController* PlayerController =
		Cast<ASCMarinePlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	if (PlayerController)
	{
		PlayerController->UpdateAmmoCount(CurrentAmmo);
	}
	return;
}


void ASCMWeapon::PlayGunshotSFX(AActor* PossessedActor)
{
	if (Gunshot)
	{
		UGameplayStatics::PlaySoundAtLocation(this, Gunshot, GetActorLocation(), 1.0f, FMath::RandRange(0.9f, 1.0f));
		//UGameplayStatics::PlaySoundAtLocation(this, Gunshot, GetActorLocation(), 1.0f, 1.0f);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to play Gunshot"));
	}
	return;
}


