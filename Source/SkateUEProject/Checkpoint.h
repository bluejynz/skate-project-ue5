// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Checkpoint.generated.h"

UCLASS()
class SKATEUEPROJECT_API ACheckpoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckpoint();

	// Collider component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
	int ScoreValue;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Collider component
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USphereComponent* SphereCollider;

	UFUNCTION()
	void OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
