// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Game_One.h"
#include "Pickup.h"
#include "Game_OneCharacter.h"

AGame_OneCharacter::AGame_OneCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->RelativeRotation = FRotator(0.f,180.f,0.f);

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	//create the collection sphere of the character and then connect it to the characters root component
	CollectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollectionSphere"));
	CollectionSphere->AttachTo(RootComponent);
	CollectionSphere->SetSphereRadius(CollectionSphereRadius);

	////Inventory Size
	MaxInventorySize = 5;

	//Characters inventory 
	UPROPERTY(VisibleAnywhere)
	Inventory.SetNum(MaxInventorySize);
}

//////////////////////////////////////////////////////////////////////////
// Input

void AGame_OneCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// set up gameplay key bindings
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	InputComponent->BindAxis("MoveRight", this, &AGame_OneCharacter::MoveRight);

	InputComponent->BindTouch(IE_Pressed, this, &AGame_OneCharacter::TouchStarted);
	InputComponent->BindTouch(IE_Released, this, &AGame_OneCharacter::TouchStopped);

	//input for collecting pickups from the environment
	InputComponent->BindAction("Collect Item", IE_Pressed, this, &AGame_OneCharacter::CollectPickups);


}

void AGame_OneCharacter::CollectPickups() {
	
	//get all overlapping actors and then store than into an array
	TArray<AActor*> PotentialPickupsInRange;
	CollectionSphere->GetOverlappingActors(PotentialPickupsInRange);

	//for each actor that we collect 
	for (int32 collectedItem = 0; collectedItem < PotentialPickupsInRange.Num() ; ++collectedItem) {
		
		//Try to cast the actors to Pickup
		APickup* const Test = Cast<APickup>(PotentialPickupsInRange[collectedItem]);

		//if of type pickup and the pickup is active (ready for pickup)
		if (Test && !Test->IsPendingKill() && Test->IsActive()) {

			//call this version of Collected() as it will capture any Blueprint script we may use to override the function
			Test->Collected();

			//deactivate the item we picked up
			Test->SetActive(false);
		}

		//then call teh pickups was collectied function and then deactivate the pickup
	}
		
}

void AGame_OneCharacter::MoveRight(float Value)
{
	// add movement in that direction
	AddMovementInput(FVector(0.f,-1.f,0.f), Value);
}

void AGame_OneCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	Jump();
}

void AGame_OneCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}

void AGame_OneCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Initializing our reference
	LastItemSeen = nullptr;
}

void AGame_OneCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//Update inventory evey tick

}
