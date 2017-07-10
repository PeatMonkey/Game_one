// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pickup.h"
#include "UObjectGlobals.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "Game_One.h"
#include "MemoryPickup.generated.h"

/**
 * 
 */
UCLASS()
class GAME_ONE_API AMemoryPickup : public APickup {
	GENERATED_BODY()

public:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Sets default values for this actor's properties
	AMemoryPickup();
	
	//overide the Collected function
	void Collected_Implementation() override;

	bool CollectPickup() override;
protected:

	USplineComponent* SplineComp = nullptr;

private:
	
	void MoveTowards();

	bool bIsMoving = false;

	float SplineDistance = 0.0;
	float CurrentDistance = 0.0;

	FVector CurrentLocation;
	FRotator CurrentRotation;
	
};
