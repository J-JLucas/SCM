// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SCMProjectile.generated.h"

UCLASS()
class SCMARINE_API ASCMProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASCMProjectile();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Dodgeball, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Dodgeball, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* PrjMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Damage)
	float Damage = 34.0f;

	UPROPERTY(EditAnywhere, Category = Sound)
	class USoundBase* FlyingSound;

	UPROPERTY(EditAnywhere, Category = Sound)
	class USoundBase* ImpactSound;

	UPROPERTY(EditAnywhere, Category = Sound)
	class USoundBase* DamageSound;

	//UPROPERTY(EditAnywhere, Category = Sound)
	//	class USoundAttenuation* BounceSoundAttenuation;

	UPROPERTY(EditAnywhere, Category = Particles)
	class UParticleSystem* HitParticles;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// Function that initializes the projectile's velocity in the shoot direction
	void FireInDirection(const FVector& ShootDirection);

	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovementComponent() const { return ProjectileMovement; }


};
