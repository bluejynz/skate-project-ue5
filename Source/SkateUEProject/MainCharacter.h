// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UCLASS()
class SKATEUEPROJECT_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

	/** Camera boom positioning the camera bihind the player */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/** Base turn rates to scale turning functions for the camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	/** Pointer to the existing ArrowComponent */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UArrowComponent* MovementDirectionArrow;

	/** Speed for rotation */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	float RotationSpeed;

	/** Maximum movement speed */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float MaxSpeed;

	/** Rate for accelaration */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float AccelerationRate;

	/** Rate for decelaration */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float DecelerationRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float CurrentSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	bool bIsAccelerating;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Called for forwards input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** Called to manage acceleration/deceleration */
	void ManageAcceleration(float DeltaTime);

	// Input functions for mouse movement
	void Turn(float Rate);
	void LookUp(float Rate);

};
