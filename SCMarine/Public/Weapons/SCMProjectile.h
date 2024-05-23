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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* PrjMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Damage)
	float Damage = 10.0f;

	UPROPERTY(EditAnywhere, Category = Sound)
	class USoundBase* FlyingSound;

	UPROPERTY(EditAnywhere, Category = Sound)
	class USoundBase* ImpactSound;

	UPROPERTY(EditAnywhere, Category = Sound)
	class USoundBase* DamageSound;

	UPROPERTY(EditAnywhere, Category = Particles)
	class UParticleSystem* HitParticles;

	UPROPERTY(EditDefaultsOnly, Category = Particles)
	class UNiagaraSystem* HitSystem;

	UPROPERTY(EditAnywhere, Category = Particles)
	class UParticleSystem* FlyingParticles;

	UPROPERTY(EditAnywhere, Category = Impulse)
	float ImpulseStrength = 0.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// Function that initializes the projectile's velocity in the shoot direction
	void FireInDirection(const FVector& ShootDirection);

	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovementComponent() const { return ProjectileMovement; }

};
