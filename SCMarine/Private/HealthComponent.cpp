// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "HealthInterface.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerState.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;		// init character health

	AActor* Owner = GetOwner();
	
	/* bind TakeDamge function to OnTakeAnyDamage */
	// Whenever OnTakeAnyDamage event occurs, TakeDamage will automatically execute
	// OnTakeAnyDamage is a blanket event that executes for multiple functions
	// for example in SCMHitScanWeapon.cpp we call ApplyPointDamage to trigger event
	if (Owner) 
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
	}
}

void UHealthComponent::SetMaxHealth(float Value)
{
	MaxHealth = Value;
	Health = MaxHealth;
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0) { return; }
	
	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
	if (Health > 0.0f)
	{
		if (InjuredSound)
		{

			UGameplayStatics::PlaySoundAtLocation(this, InjuredSound, GetOwner()->GetActorLocation(), 1.0f, 1.0f);
			//supply pitch multiplier factor between random range of specified floats
		}
	}

	if (GetOwner()->Implements<UHealthInterface>())
	{
		IHealthInterface::Execute_OnTakeDamage(GetOwner());
	}

	if (Health <= 0) // Dead
	{
		bIsDead = true;
		// Dead
		if (GetOwner()->Implements<UHealthInterface>())
		{
			IHealthInterface::Execute_OnDeath(GetOwner());
			
			if (InstigatedBy)
			{
				APlayerState* PlayerState = InstigatedBy->GetPlayerState<APlayerState>();
				if (PlayerState)
				{
					PlayerState->SetScore(PlayerState->GetScore() + 1);
				}
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "No Instigator?");
			}
		}
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::SanitizeFloat(Health));
}

bool UHealthComponent::AddHealth(float Value)
{
	if (!bIsDead && Health != MaxHealth)
	{
		Health = FMath::Clamp(Health + Value, 0.0f, MaxHealth);
		UE_LOG(LogTemp, Warning, TEXT("Updated Health: %f"), Health);
		return true;
	}
	else
	{
		return false;
	}
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}