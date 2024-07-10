// Fill out your copyright notice in the Description page of Project Settings.


#include "Checkpoint.h"
#include "Components/SphereComponent.h"
#include "MainCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Construct the Collision Volume and Attach it to the RootComponent
	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionVolume"));
	SphereCollider->SetupAttachment(RootComponent);

    // Set the collision profile to overlap all dynamic objects
    SphereCollider->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	// Create Delegate and reference the function we created earlier, to call when overlapped
	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnPlayerOverlap);

    // Set ScoreValue to a default value
    ScoreValue = 120;
}

// Called when the game starts or when spawned
void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACheckpoint::OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // Check if OtherActor is not null && check if it is the Main Character
    if (OtherActor && OtherActor->IsA(AMainCharacter::StaticClass()))
    {
        AMainCharacter* PlayerCharacter = Cast<AMainCharacter>(OtherActor); // Cast to MainCharacter

        if (PlayerCharacter && PlayerCharacter->GetMovementComponent()->IsFalling())
        {
            // Add to player score using actor's score value if player is jumping
            PlayerCharacter->AddToScore(ScoreValue);
        }
    }
}

