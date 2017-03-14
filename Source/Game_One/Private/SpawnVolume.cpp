// Fill out your copyright notice in the Description page of Project Settings.

#include "Game_One.h"
#include "SpawnVolume.h"


void ASpawnVolume::SpawnPickup() {
	//if we have something to spawn
	if (WhatToSpawn != NULL) {
		
		//check for a valid world
		UWorld* const World = GetWorld();

		if (World) {
			
			//Of the things we are spawning do we know who owns them, and do we know who cuased the spawning 
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;

			//get a random location to spawn
			FVector SpawnLocation = GetRandomPoints();
			
			//give a random rotation
			FRotator SpawnRotation;
			SpawnRotation.Yaw = FMath::FRand() * 360.0f;
			SpawnRotation.Pitch = FMath::FRand() * 360.0f;
			SpawnRotation.Roll = FMath::FRand() * 360.0f;

			//Spawn the item
			APickup* const SpawnedPickup = World->SpawnActor<APickup>(WhatToSpawn, SpawnLocation, SpawnRotation, SpawnParams);

			//if we already spawned a pickup then we reset the world timer for the next respawn
			SpawnDelay = FMath::FRandRange(SpawnDelayMin, SpawnDelayMax);
			GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnPickup, SpawnDelay, false);
			
		}

		
	}
}

// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = false;

	//create the box component
	WhereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("Where to Spawn"));
	RootComponent = WhereToSpawn;

	//set the spawning range
	SpawnDelayMin = 1.0f;
	SpawnDelayMax = 4.5f;

}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnDelay = FMath::FRandRange(SpawnDelayMin, SpawnDelayMax);
	
	//Keeps track of the global timers for when the item should be spawned
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnPickup, SpawnDelay, false);
}

// Called every frame
void ASpawnVolume::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

FVector ASpawnVolume::GetRandomPoints() {

	FVector SpawnOrigin = WhereToSpawn->Bounds.Origin;
	FVector SpawnExtent = WhereToSpawn->Bounds.BoxExtent;

	return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);

}

