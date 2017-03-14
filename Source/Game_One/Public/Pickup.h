// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class GAME_ONE_API APickup : public AActor
{
	GENERATED_BODY()
private:

	//mesh of the item we are picking up
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PickupProperties", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* PickupMesh;

	//texture of the current pickup item
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PickupProperties", meta = (AllowPrivateAccess = "true"))
	//UPROPERTY(EditAnywhere, Category = "PickupProperties")
	UTexture2D* PickupTexture;

	// Name of the item
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PickupProperties", meta = (AllowPrivateAccess = "true"))
	//UPROPERTY(EditAnywhere, Category = "PickupProperties")
	FString ItemName;



public:	


	// Sets default values for this actor's properties
	APickup();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;


	/*Getters and Setters for the pickup*/

	//return whether or not the pickup is in a active pickup state
	UFUNCTION(BlueprintPure, Category = "Pickup")
	bool IsActive();

	//allows other classes to set whether this item can be picked up
	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void SetActive(bool NewPickupState);

	//Enables the glow effect around items
	void SetGlowEffect(bool Status);

	//Getters for our member variables
	FORCEINLINE class UTexture2D* GetPickupTexture() const { return PickupTexture; }
	FORCEINLINE class UStaticMeshComponent* GetMesh() const { return PickupMesh; }
	FORCEINLINE class FString GetName() const { return ItemName; }

	//This function is call ed when the item has been collected
	//BlueprintNativeEvent is a macro param that allows a function to be overriden in the blueprint
	UFUNCTION(BlueprintNativeEvent)
	void Collected();

	//overide this one in child classes as the Collected() fucntion is a BlueprintNativeEvent
	virtual void Collected_Implementation();

protected:
	//True when the item can be picked up
	bool bIsActive;

	//UPROPERTY(VisibleAnywhere)
	//UStaticMeshComponent* PickupSM;
	
};
