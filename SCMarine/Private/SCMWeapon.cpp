// Fill out your copyright notice in the Description page of Project Settings.


#include "SCMWeapon.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ASCMWeapon::ASCMWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
	//Fire
}

void ASCMWeapon::AltFire()
{
	// Reserved for future use
}

void ASCMWeapon::ReloadWeapon()
{
	// Reload
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

void ASCMWeapon::PlayGunshotSFX(AActor* PossessedActor)
{
	UGameplayStatics::SpawnSoundAtLocation(PossessedActor->GetWorld(), Gunshot, PossessedActor->GetActorLocation());
}


