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

	UPROPERTY(EditAnywhere, Category = Particles)
	FVector Scale = FVector(1.0f);

	UPROPERTY(EditAnywhere, Category = Damage)
	float Damage = 100.0f;

	UPROPERTY(EditAnywhere, Category = Sound)
	class USoundBase* ExplosionSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
