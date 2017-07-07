// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Inventory_Widget.h"
#include "Game_OneCharacter.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GAME_ONE_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	
	UInventory_Widget* InventoryWidgetRef;

	//true if the inventory is currently open
	bool bIsInventoryOpen;

protected:

	//InventoryWidget blueprint referance
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventory_Widget> InventoryWidgetBP;

public:
	virtual void Possess(APawn* InPawn) override;

	//Opens or closes the inventory
	void HandleInventoryInput();
	
};
