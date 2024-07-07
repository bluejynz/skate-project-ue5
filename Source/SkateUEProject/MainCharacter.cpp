// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/ArrowComponent.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Set the character to auto-possess player 0
    AutoPossessPlayer = EAutoReceiveInput::Player0;

    // Don't rotate when the controller rotates. Let that just affect the camera.
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    /** Create Camera boom (pulls towards the player if there's a collision) */
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 500.f; // Camera follows at this distance
    CameraBoom->bUsePawnControlRotation = true; // Rotate arm based on controller

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    // Attach the camera to the end of the boom and let the boom adjust to match
    // the controller orientation
    FollowCamera->bUsePawnControlRotation = false;

    // Set turn rates for input
    BaseTurnRate = 65.f;
    BaseLookUpRate = 65.f;

    // Initialize the pointer to the existing ArrowComponent
    MovementDirectionArrow = FindComponentByClass<UArrowComponent>();

}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    check(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);

}

void AMainCharacter::MoveForward(float Value)
{
    if ((Controller != nullptr) && (Value != 0.0f) && MovementDirectionArrow)
    {
        // Determine the forward direction based on the arrow component
        const FVector Direction = MovementDirectionArrow->GetForwardVector();
        AddMovementInput(Direction, Value);
    }
}

void AMainCharacter::MoveRight(float Value)
{
    if ((Controller != nullptr) && (Value != 0.0f) && MovementDirectionArrow)
    {
        // Determine the right direction based on the arrow component
        const FVector Direction = MovementDirectionArrow->GetRightVector();
        AddMovementInput(Direction, Value);
    }
}

