// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Pickup.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"


UCLASS()
class GAME_ONE_API ASpawnVolume : public AActor
{
	GENERATED_BODY()


private:

	//Component where the inventory pickups should be spawned
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning Location", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* WhereToSpawn;

	//handle the spawning of items
	void SpawnPickup();

	//store the spawn delay
	float SpawnDelay;

protected:

	//item to spawn
	//will force that ownly members of the APickup class and children can set on this variable
	UPROPERTY(EditAnywhere, Category = "Spawning Location")
	TSubclassOf<class APickup> WhatToSpawn;

	//Create a timer handle
	FTimerHandle SpawnTimer;

	//min spawn delay
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning Location")
	float SpawnDelayMin;

	//max spawn delay
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning Location")
	float SpawnDelayMax;

public:	
	// Sets default values for this actor's properties
	ASpawnVolume();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//getters ans setters
	FORCEINLINE class UBoxComponent* GetWhereToSpawn() const { return WhereToSpawn; }

	//BlueprintPure, means that there wil be no execution pins
	UFUNCTION(BlueprintPure, Category = "Spawning Location")
	FVector GetRandomPoints();

	
};
