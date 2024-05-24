// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/SCMProjectileFlame.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy/SCMEnemy.h"


void ASCMProjectileFlame::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	ASCMEnemy* Enemy = Cast<ASCMEnemy>(OtherActor);

	if (ImpactSound && !Enemy)
	{
		//supply pitch multiplier factor between random range of specified floats
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), 1.0f, FMath::RandRange(0.9f, 1.1f), 0.0f);
	}

	if (Enemy)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, "Hit a Enemy");
		UGameplayStatics::ApplyDamage(OtherActor, Damage, GetInstigatorController(), this, nullptr);
		if (DamageSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, DamageSound, GetActorLocation(), 1.0f, FMath::RandRange(0.9f, 1.1f), 0.0f);
		}
	}

	if (HitParticles && Enemy)
	{
		FVector Location = FVector::ZeroVector;;
		FRotator Rotation = FRotator::ZeroRotator;;
		FVector Scale = FVector(2.0f);
		//UGameplayStatics::SpawnEmitterAttached(HitParticles, OtherComp, NAME_None, Location, Rotation, Scale, EAttachLocation::SnapToTarget, true);

	}
	Destroy();

	return;
}