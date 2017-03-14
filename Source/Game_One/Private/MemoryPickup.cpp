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
