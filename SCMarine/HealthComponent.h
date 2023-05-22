// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SCMARINE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:

	// Called when the game starts
	virtual void BeginPlay() override;

	// Max health value
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DaHealthy?")
	float MaxHealth = 100.0f;

	// Current health
	UPROPERTY(BlueprintReadOnly)
	float Health = MaxHealth;

		
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION(BlueprintCallable)
	void SetMaxHealth(float Value);

	FORCEINLINE float GetHealthPercent() const { return (Health / MaxHealth); }
		
};
