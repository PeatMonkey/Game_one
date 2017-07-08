// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pickup.h"
#include "GameFramework/Actor.h"
#include "Game_One.h"
#include "MemoryPickup.generated.h"

/**
 * 
 */
UCLASS()
class GAME_ONE_API AMemoryPickup : public APickup
{
	GENERATED_BODY()

public:

	// Sets default values for this actor's properties
	AMemoryPickup();
	
	//overide the Collected function
	void Collected_Implementation() override;

	bool CollectPickup() override;
private:
	
	//UProjectileMovementComponent* ProjectileMovement = nullptr;
	
};
