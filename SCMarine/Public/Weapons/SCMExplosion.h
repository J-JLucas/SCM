// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SCMExplosion.generated.h"

UCLASS()
class SCMARINE_API ASCMExplosion : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ASCMExplosion();

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Explosion, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* SphereComponent;

	//UPROPERTY(EditAnywhere, Category = Particles)
	//class UParticleSystem* ExplosionParticles;

	TSet<AActor*> AffectedActors;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Sound)
	class USoundBase* ExplosionSound;

	UPROPERTY(EditAnywhere, Category = Particles)
	FVector Scale = FVector(1.0f);

	UPROPERTY(EditAnywhere, Category = Damage)
		float DamageValue = 100.0f;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
