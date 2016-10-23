// Fill out your copyright notice in the Description page of Project Settings.

#include "Game_One.h"
#include "HumanoidCharacterPawn.h"


// Sets default values
AHumanoidCharacterPawn::AHumanoidCharacterPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHumanoidCharacterPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHumanoidCharacterPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AHumanoidCharacterPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

