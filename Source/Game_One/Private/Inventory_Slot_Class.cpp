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
	//assign a texture if the pickup item is valid
	(Item) ? ItemTexture = Item->GetPickupTexture() : ItemTexture = nullptr;
}

