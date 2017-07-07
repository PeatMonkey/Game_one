// Fill out your copyright notice in the Description page of Project Settings.

#include "Game_One.h"
#include "Game_OneCharacter.h"
#include "MyPlayerController.h"


void AMyPlayerController::Possess(APawn* InPawn) {
	Super::Possess(InPawn);

	if (InventoryWidgetBP) {
		
		//Create the Inventory Widget based on the Blueprint reference we will input from within the Editor
		InventoryWidgetRef = CreateWidget<UInventory_Widget>(this, InventoryWidgetBP);

	}

	//Initial value
	bIsInventoryOpen = false;
}

void AMyPlayerController::HandleInventoryInput() {
	AGame_OneCharacter* Char = Cast<AGame_OneCharacter>(GetPawn());
	
	if (InventoryWidgetRef) {
		if (bIsInventoryOpen) {
			//Mark the inventory as closed
			bIsInventoryOpen = false;

			//Remove it from the viewport
			InventoryWidgetRef->RemoveFromViewport();
		} else {
			//Mark the inventory as open
			bIsInventoryOpen = true;

			//Pass along a pointer to the items that the character has picked for inventory
			InventoryWidgetRef->ItemsArray = Char->GetInventory();

			//Show the inventory
			InventoryWidgetRef->Show();
		}

	}
}

