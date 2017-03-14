// Fill out your copyright notice in the Description page of Project Settings.

#include "Game_One.h"
#include "TP_Guard_Animation.h"

bool UTP_Guard_Animation::setEnableJump(bool Condition) {
	
	if (Condition) {
		this->EnableJump = true;
		return true;
	}
	else {
		this->EnableJump = false;
		return false;
	}
}

bool UTP_Guard_Animation::getEnableJump() {
	return this->EnableJump;
}

void UTP_Guard_Animation::UpdateAnimationProperties() {
	//get the pawn
	APawn* Pawn = TryGetPawnOwner();


	if (Pawn) {
		//update our falling property
		this->isFalling = Pawn->GetMovementComponent()->IsFalling();
	}

	//update the movement property
	this->MovementSpeed = Pawn->GetVelocity().Size();
}

bool UTP_Guard_Animation::Can_Jump(bool ShouldJump, UTP_Guard_Animation* Target)
{

	if (ShouldJump == Target->EnableJump) {
		return true; 
	}
	else {
		return false;
	}
}
