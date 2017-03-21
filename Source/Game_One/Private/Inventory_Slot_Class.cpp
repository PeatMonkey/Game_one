// Fill out your copyright notice in the Description page of Project Settings.

#include "Game_One.h"
#include "Pickup.h"
#include "Inventory_Slot_Class.h"

void UInventory_Slot_Class::SetEquippedItem()
{
	//Empty for now
}

void UInventory_Slot_Class::SetItemTexture(APickup* Item)
{
	//If the item is valid update the widget's texture.
	//If not, assign a null ptr to it so the widget won't broadcast wrong information to the player
	(Item) ? ItemTexture = Item->GetPickupTexture() : ItemTexture = nullptr;
}

