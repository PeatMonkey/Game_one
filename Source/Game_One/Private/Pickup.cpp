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

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	RootComponent = PickupMesh;

	//variables for the memory pickup
	bIsActive = true;

	//set the default pickup behavior
	PickupBehavior = EPickupBehavior::ET_Highlight;

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
	if (this != nullptr) {
		PickupMesh->SetRenderCustomDepth(Status);
	}
	
}

void APickup::Collected_Implementation()
{
}

bool APickup::ActivatePickup() {
	
	FString DebugString = GetName();
	UE_LOG(LogClass, Log, TEXT("You have collected %s"), *DebugString);
	return this->Destroy();

}

EPickupBehavior APickup::RequestPickup()
{
	return PickupBehavior;
}

