// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "TP_Guard_Animation.generated.h"

/**
 * 
 */
UCLASS()
class GAME_ONE_API UTP_Guard_Animation : public UAnimInstance
{
	GENERATED_BODY()
	
protected:

	//is true when we are currently in the air or falling 
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool isFalling;
	
	//Speed of the current character
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Crouching;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool EnableJump = true;


	/*Getters ans Setters*/
	UFUNCTION(BlueprintCallable, Category = "Set Jump")
	bool setEnableJump(bool Condition);

	UFUNCTION(BlueprintCallable, Category = "Get Jump")
	bool getEnableJump();

	/*Helper Funtions*/

	//updates the Movement Speed and the falling protected variables
	UFUNCTION(BlueprintCallable, Category = "UpdateAnimationProperties")
	void UpdateAnimationProperties();

	UFUNCTION(BlueprintCallable, Category = "Can Jump")
	bool Can_Jump(bool ShouldJump, UTP_Guard_Animation* Target);
};
