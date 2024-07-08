// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SKATEUEPROJECT_API UMainCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly, Category = "Animation")
    float speed;

    UPROPERTY(BlueprintReadOnly, Category = "Animation")
    bool bIsStopped;

    UPROPERTY(BlueprintReadOnly, Category = "Animation")
    bool bIsStopping;

    UPROPERTY(BlueprintReadOnly, Category = "Animation")
    bool bIsPaddling;

    UPROPERTY(BlueprintReadOnly, Category = "Animation")
    bool bIsJumping;

    virtual void NativeInitializeAnimation() override;
    virtual void NativeUpdateAnimation(float DeltaTime) override;

private:
    /** Main character reference */
    class AMainCharacter* PlayerCharacter;
	
};
