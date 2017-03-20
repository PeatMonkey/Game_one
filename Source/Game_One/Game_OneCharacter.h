// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "Pickup.h"
#include "GameFramework/Character.h"
#include "Game_OneCharacter.generated.h"


UCLASS(config=Game)
class AGame_OneCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;


	/*Create a collection Sphere for the character to grab items from the game world*/
	class USphereComponent* CollectionSphere;


protected:

	/** Called for side to side input */
	void MoveRight(float Val);

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	
	//Calculate distace between character and AActor
	float CalcDistanceBetweenPawnAndActor(AActor* Object);

	//Find the closest Pickup item within the collection sphere. Returns False if nothing is found;
	bool ClosestPickupWithinCollectionRange(APickup* Object);

	//Collect pickup in focus and then store it in our inventory
	UFUNCTION(BlueprintCallable, Category = "Inventory Pickups")
	void CollectPickups();

	//Called every from ato detect inventory items 
	UFUNCTION(BlueprintCallable, Category = "Inventory Pickups")
	void ScanForPickups();

	//Cycle through each nearby pickup items and apply outline effect
	UFUNCTION(BlueprintCallable, Category = "Inventory Pickups")
	void NextNearbyPickup();

	//UFUNCTION(BlueprintCallable, Category = "Inventory Pickups")

	//Last Pickup item seen
	APickup* LastItemSeen;

	//current pickup in focus
	APickup* PickupInFocus;

	//Inventory Size
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Inventory")
	int MaxInventorySize;

	//Characters inventory 
	UPROPERTY(VisibleAnywhere)
	TArray<APickup*> Inventory;

	//Items that are currently in the collection sphere of the character
	TArray<APickup*> NearbyItems;

	


public:
	//the radius that the collction sphere will extend out from the characters root component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collection Sphere")
	float CollectionSphereRadius = 500.0f;
	
	AGame_OneCharacter();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/*Returns the CollectionSphere Subobject*/
	FORCEINLINE class USphereComponent* GetCollectionSphere() const { return CollectionSphere; }

	//called when the level is loaded
	void BeginPlay();

	//called every frame
	//void Tick(float DeltaSeconds);

};