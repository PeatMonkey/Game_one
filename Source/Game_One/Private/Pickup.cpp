// Fill out your copyright notice in the Description page of Project Settings.

#include "Game_One.h"
#include "Pickup.h"


// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Variabels for inventory items
	//PickupSM = CreateDefaultSubobject<UStaticMeshComponent>(FName("PickupSM"));
	PickupTexture = CreateDefaultSubobject<UTexture2D>(FName("ItemTexture"));

	//variables for the memory pickup
	bIsActive = true;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	RootComponent = PickupMesh;

}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickup::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

bool APickup::IsActive() {
	return bIsActive;
}


//Getters and Setters
void APickup::SetActive(bool NewPickupState) {
	bIsActive = NewPickupState;
}

//ensure we highlight the item that we pick up
void APickup::SetGlowEffect(bool Status) {
	PickupMesh->SetRenderCustomDepth(Status);
}

