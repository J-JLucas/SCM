// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "Public/HealthInterface.h"
#include "SCMPlayerCharacter.generated.h"

UCLASS()
class SCMARINE_API ASCMPlayerCharacter : public ACharacter, public IHealthInterface
{
	GENERATED_BODY()

private:

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputMappingContext* IC_PlayerChar;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* IA_Movement;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* IA_Look;

	//** Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* IA_Fire;

	//** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* IA_Jump;

public:
	// Sets default values for this character's properties
	ASCMPlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for look input */
	void Look(const FInputActionValue& Value);	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// FPS camera
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FPSCameraComponent;

	// FPS mesh (arms); visible only to owning player
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* FPSMesh;

	// Function that handles firing projectiles
	UFUNCTION()
	void Fire();

	// Health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthComponent")
	class UHealthComponent* HealthComponent;

	virtual void OnDeath_Implementation() override;

	UPROPERTY(VisibleAnywhere)
	class AHSRifle* Rifle;

	UPROPERTY(VisibleAnywhere)
	class APlayerController* PController;

	UPROPERTY(VisibleAnywhere)
	class AActor* PossessedActor;

	void OnTakeDamage_Implementation() override;
};
