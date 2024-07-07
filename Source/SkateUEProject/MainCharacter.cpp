// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/Engine.h"

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

    // Set speed when turning sideways
    RotationSpeed = 30.f;

    MaxSpeed = 1400.f;
    AccelerationRate = 500.f;
    DecelerationRate = 500.f;

    CurrentSpeed = 0.f;
    bIsAccelerating = false;

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

    ManageAcceleration(DeltaTime);
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    check(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveSideways", this, &AMainCharacter::MoveRight);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
}

void AMainCharacter::MoveForward(float Value)
{
    if ((Controller != nullptr) && (Value != 0.0f))
    {
        bIsAccelerating = true;

    }
    else 
    {
        bIsAccelerating = false;
    }
}

void AMainCharacter::MoveRight(float Value)
{
    if ((Controller != nullptr) && (Value != 0.0f))
    {
        // Calculate rotation speed based on current speed
        float ModifiedRotationSpeed = RotationSpeed + (CurrentSpeed * .01f);

        // Rotate character in input's direction
        AddControllerYawInput(Value * ModifiedRotationSpeed * GetWorld()->GetDeltaSeconds());
    }
}

void AMainCharacter::ManageAcceleration(float DeltaTime)
{
    if (bIsAccelerating)
    {
        CurrentSpeed = FMath::Min(CurrentSpeed + AccelerationRate * DeltaTime, MaxSpeed);
    }
    else
    {
        CurrentSpeed = FMath::Max(CurrentSpeed - DecelerationRate * DeltaTime, 0.f);
    }

    // Moves forward int the direction of the character's foward direction and add movement
    const FVector Direction = GetActorForwardVector();
    AddMovementInput(Direction, CurrentSpeed);

    GetCharacterMovement()->MaxWalkSpeed = CurrentSpeed;
}

