// Fill out your copyright notice in the Description page of Project Settings.


#include "SCMProjectileHydra.h"
#include "Kismet/GameplayStatics.h"
#include "SCMarine/SCMPlayerCharacter.h"

void ASCMProjectileHydra::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (ImpactSound)
	{
		//supply pitch multiplier factor between random range of specified floats
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), 1.0f, FMath::RandRange(0.9f, 1.1f), 0.0f);
	}

	ASCMPlayerCharacter* Player = Cast<ASCMPlayerCharacter>(OtherActor);

	if (Player)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, "Hit a Player");
		UGameplayStatics::ApplyDamage(OtherActor, Damage, GetInstigatorController(), this, nullptr);
		if (DamageSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, DamageSound, GetActorLocation(), 1.0f, FMath::RandRange(0.9f, 1.1f), 0.0f);
		}
	}

	if (HitParticles && Player)
	{
		//FVector Location = FVector::ZeroVector;;
		FRotator Rotation = FRotator::ZeroRotator;;
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticles, GetActorLocation(), Rotation, true);
	}

	Destroy();

	return;
}

