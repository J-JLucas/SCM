// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/SCMWeapon.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "SCMarinePlayerController.h"
#include "SCMPlayerCharacter.h"

// Sets default values
ASCMWeapon::ASCMWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bCanSwitchWeapons = true;
}

// Called when the game starts or when spawned
void ASCMWeapon::BeginPlay()
{
	Super::BeginPlay();
	SetOwnerReferences();
}

void ASCMWeapon::SetOwnerReferences()
{
	PlayerController = Cast<ASCMarinePlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	if (PlayerController)
	{
		auto* const Pawn =  PlayerController->GetPawn();
		PlayerChar = Cast<ASCMPlayerCharacter>(Pawn);
		if (!PlayerChar)
		{
			UE_LOG(LogTemp, Error, TEXT("No Valid Player Pawn found."));
		}
		SetOwner(PlayerChar);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Valid Player Controller found."));
	}
}

// Called every frame
void ASCMWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASCMWeapon::PrimaryFire()
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

	if ((CurrentAmmo == 0) || (CurrentMag == MaxMag)) { return; }
	StartReloading();
	// 3d models are part of player, triggers event in playercharacter and PC w/ play the animation
	if (PlayerChar)
	{
		PlayerChar->OnReloadEvent();
	}
	else (GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "No Valid PlayerChar"));
	return;
}

bool ASCMWeapon::AddAmmo(int Amount)
{
	if (CurrentAmmo != MaxAmmo)
	{
		CurrentAmmo = FMath::Clamp(CurrentAmmo + Amount, 0, MaxAmmo);
		UE_LOG(LogTemp, Warning, TEXT("Updated AmmoReserve: %d"), CurrentAmmo);
		return true;
	}
	else
	{
		return false;
	}
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

void ASCMWeapon::PlayFireAnimation()
{
	// 3d models are part of player, triggers event in playercharacter and PC w/ play the animation
	if (PlayerChar)
	{
		PlayerChar->OnFireEvent();
	}

}

void ASCMWeapon::StartFiring()
{
	bIsFiring = true;
	bCanSwitchWeapons = false;
	GetWorldTimerManager().SetTimer(FireHandle, this, &ASCMWeapon::StopFiring, FireRate, false);
	return;
}

void ASCMWeapon::StopFiring()
{
	GetWorldTimerManager().ClearTimer(FireHandle);
	bIsFiring = false;
	bCanSwitchWeapons = true;
	return;
}

void ASCMWeapon::StartReloading()
{
	bIsReloading = true;
	bCanSwitchWeapons = false;
	GetWorldTimerManager().SetTimer(ReloadHandle, this, &ASCMWeapon::StopReloading, ReloadRate, false);
	
}

void ASCMWeapon::StopReloading()
{
	GetWorldTimerManager().ClearTimer(ReloadHandle);
	bIsReloading = false;
	bCanSwitchWeapons = true;

	float BulletsNeeded = MaxMag - CurrentMag;

	if (BulletsNeeded > CurrentAmmo)
	{
		CurrentMag += CurrentAmmo;
		CurrentAmmo = 0;

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
}

void ASCMWeapon::SetRangeAmount(float RangeValue)
{
	Range = RangeValue;
}

void ASCMWeapon::UpdateMagString()
{
	if (PlayerController)
	{
		PlayerController->UpdateMagCount(CurrentMag);
	}
	return;
}
void ASCMWeapon::UpdateAmmoString()
{
	if (PlayerController)
	{
		PlayerController->UpdateAmmoCount(CurrentAmmo);
	}
	return;
}


void ASCMWeapon::SetAbleToSwitch(bool Status)
{
	bCanSwitchWeapons = Status;
}
