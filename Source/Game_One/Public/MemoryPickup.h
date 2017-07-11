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

	//Event fired to activate and collect the pickup
	bool ActivatePickup() override;

	//tells caller what behavior to expect from the pickup
	EPickupBehavior RequestPickup() override;

protected:
	
	//curve that is to be followed by the pickup
	USplineComponent* SplineComp = nullptr;

private:
	
	//function to be called every frame in order to move pickup towards that destination
	void MoveTowards();

	//flag to indicate movement
	bool bIsMoving = false;

	//the length of the spline between origin and destination location
	float SplineDistance = 0.0;
	float CurrentDistance = 0.0;

	int MovementSpeed = 20;

	//current location and rotation of the pickup during its movement
	FVector CurrentLocation;
	FRotator CurrentRotation;
	
};
