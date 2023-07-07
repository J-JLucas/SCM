// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableActor_Base.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SCMarine/SCMPlayerCharacter.h"


// Sets default values
APickableActor_Base::APickableActor_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(80.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("OverlapAllDynamic");
	RootComponent = CollisionComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	RotationComp = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotationComp"));

}

// Called when the game starts or when spawned
void APickableActor_Base::BeginPlay()
{
	Super::BeginPlay();
	
	// arms BeginOverlap to be called when overlap event w/ CollisionComp occurs
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &APickableActor_Base::BeginOverlap);

}


void APickableActor_Base::PlayerPickedUp(ASCMPlayerCharacter* PlayerChar)
// called when the player overlaps the pickup item
{
	UWorld* World = GetWorld();
	UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation(), 1.0f);
	Destroy();
}


void APickableActor_Base::BeginOverlap(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	ASCMPlayerCharacter* PlayerChar = Cast<ASCMPlayerCharacter>(OtherActor);
	if (PlayerChar)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("PlayerOverlap w/ Crate"));
		PlayerPickedUp(PlayerChar);
	}
}


