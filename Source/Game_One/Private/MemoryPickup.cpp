// Fill out your copyright notice in the Description page of Project Settings.

#include "Game_One.h"
#include "MemoryPickup.h"

//set default values
AMemoryPickup::AMemoryPickup() {

	//as soon as the battery is initialized physics propery wil be enabled
	GetMesh()->SetSimulatePhysics(true);

}

void AMemoryPickup::Collected_Implementation() {
	// use the base pickup behavior
	Super::Collected_Implementation();

	//get ride of the item after the pickup
	Destroy();
}

bool AMemoryPickup::CollectPickup() {
	this->Destroy();
	//FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetActorLocation();

	//ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * 5.0);

	//Again, this is provented from firing right at the get-go because we set ProjectileMovement->bAutoActivate = false;
	//ProjectileMovement->Activate();

	return true;
}
