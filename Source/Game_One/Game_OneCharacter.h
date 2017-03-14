// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
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
	

	//Called when we press a key for collecting the pickups
	UFUNCTION(BlueprintCallable, Category = "Inventory Pickups")
	void CollectPickups();
	
	
	// End of APawn interface



public:
	//the radius that the collction sphere will extend out from the characters root component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collection Sphere")
	float CollectionSphereRadius = 200.0f;
	
	AGame_OneCharacter();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/*Returns the CollectionSphere Subobject*/
	FORCEINLINE class USphereComponent* GetCollectionSphere() const { return CollectionSphere; }

};