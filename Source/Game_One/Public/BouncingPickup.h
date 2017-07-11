// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pickup.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Components/TimelineComponent.h"
#include "BouncingPickup.generated.h"

/**
 * 
 */
UCLASS()
class GAME_ONE_API ABouncingPickup : public APickup
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	ABouncingPickup();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	bool ActivatePickup() override;

	//The maximum height value that the actor is going to reach.
	UPROPERTY(EditAnywhere, Category = "Timeline")
		float MaxBounceHeight;

	//Curve float reference
	UPROPERTY(EditAnywhere, Category = "Timeline")
		UCurveFloat* CurveFloat;

private:
	

	//The initial location of the actor
	FVector ActorInitialLocation;

	//The target location which is based on the max bounce height
	FVector TargetLocation;

	//The timeline that will make the actor float
	FTimeline MyTimeline;

	//The function that will handle every tick of the float curve
	UFUNCTION()
	void HandleProgress(float Value);

	
	
};
