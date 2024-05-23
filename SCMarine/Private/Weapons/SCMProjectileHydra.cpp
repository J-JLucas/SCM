// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/SCMProjectileHydra.h"
#include "Kismet/GameplayStatics.h"
#include "SCMPlayerCharacter.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

ASCMProjectileHydra::ASCMProjectileHydra()
	:Super()
{
	ImpulseStrength = 1000.0f;
}

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
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, "Hit a Player");
		FVector ImpulseDirection = GetActorLocation() - OtherActor->GetActorLocation();
		ImpulseDirection.Normalize();

		UGameplayStatics::ApplyDamage(OtherActor, Damage, GetInstigatorController(), this, nullptr);
		Player->LaunchCharacter(-ImpulseDirection * ImpulseStrength, true, true);


		if (DamageSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, DamageSound, GetActorLocation(), 1.0f, FMath::RandRange(0.9f, 1.1f), 0.0f);
		}
	}

	if (HitSystem)
	{
		//FVector Location = FVector::ZeroVector;;
		FRotator Rotation = FRotator::ZeroRotator;;
		//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticles, GetActorLocation(), Rotation, true);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), HitSystem, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
	}

	Destroy();

	return;
}

