// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LockableDoor.generated.h"

UCLASS()
class SCMARINE_API ALockableDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALockableDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* DoorMesh;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* ActivationBox;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* LeftCollisionBox;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* RightCollisionBox;

	FTimerHandle DoorTimerHandle;
	float DoorTimerLength{ 5.0f };
	virtual void StartDoorTimer();
	virtual void StopDoorTimer();


	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void EndOverlap(UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

public:	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Key)
	TEnumAsByte<enum KeyType> LockType {0};

	bool bIsLocked{true};

	UPROPERTY(BlueprintReadWrite, Category = Door)
	bool bDoorIsOpen{false};

};
