// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacterAnimInstance.h"
#include "MainCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMainCharacterAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    PlayerCharacter = Cast<AMainCharacter>(TryGetPawnOwner());

    bIsStopped = true;
    bIsPaddling = false;
    bIsJumping = false;
    bIsStopping = false;
    speed = 0.f;
}

void UMainCharacterAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
    Super::NativeUpdateAnimation(DeltaTime);

    if (PlayerCharacter)
    {
        // Update character current speed
        speed = PlayerCharacter->CurrentSpeed;

        // Update bIsJumping based on character being in air
        bIsJumping = PlayerCharacter->GetMovementComponent()->IsFalling();

        // Update bIsStopped based on character input acceleration and current speed
        bIsStopped = !PlayerCharacter->bIsAccelerating && PlayerCharacter->CurrentSpeed <= 0.f && !bIsJumping;

        // Update bIsStopping based on character input acceleration and current speed
        bIsStopping = !PlayerCharacter->bIsAccelerating && PlayerCharacter->CurrentSpeed > 0.f && !bIsJumping;

        // Update bIsPaddling based on character input acceleration and current speed
        bIsPaddling = PlayerCharacter->bIsAccelerating && PlayerCharacter->CurrentSpeed > 0.f && !bIsJumping;
    }
}

