// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Game_One.h"
#include "Pickup.h"
#include "MyPlayerController.h"
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

	MaxInventorySize = 5;

	PickupInFocus = nullptr;

	Inventory.SetNum(MaxInventorySize);

	RaycastRange = NULL;
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

	//Scan for pickup items in the nearby area
	InputComponent->BindAction("Scan for Nearby Pickup Items", IE_Pressed, this, &AGame_OneCharacter::ScanForPickups);

	//input for cycling through the items that are currently in the collection Sphere 
	InputComponent->BindAction("Cycle Next Pickup Item", IE_Pressed, this, &AGame_OneCharacter::NextNearbyPickup);

	//input for collecting pickups from the environment
	InputComponent->BindAction("Collect Item", IE_Pressed, this, &AGame_OneCharacter::CollectPickups);

	//hide or show the current inventory
	InputComponent->BindAction("Show Inventory", IE_Pressed, this, &AGame_OneCharacter::HandleInventoryInput);

}

float AGame_OneCharacter::CalcDistanceBetweenPawnAndActor(AActor * Object)
{
	float distance = 0.0f;
	FVector VectorDifference;
	VectorDifference = this->GetActorLocation() - Object->GetActorLocation();
	
	distance = VectorDifference.Size();
	
	return distance;
}

bool AGame_OneCharacter::ClosestPickupWithinCollectionRange(APickup * Object)
{
	float ShortestDistance = 0;

	if (NearbyItems.Num() == 0) {
		return false;
	}


	float temp = 0;

	for (int Pickup = 0; Pickup < NearbyItems.Num(); Pickup++) {
		temp = CalcDistanceBetweenPawnAndActor(Cast<AActor>(NearbyItems[Pickup]));

		if (temp >= ShortestDistance) {
			Object = NearbyItems[Pickup];
			ShortestDistance = temp;
		}
	}


	/* for (APickup* Pickup : NearbyItems) {
		temp = CalcDistanceBetweenPawnAndActor(Cast<AActor>(Pickup));

		if (temp >= ShortestDistance) {
			Object = Pickup;
			ShortestDistance = temp;
		}
	} */
	
	return true;
}

void AGame_OneCharacter::CollectPickups() {
	

	//if of type pickup and the pickup is active (ready for pickup)
	if (PickupInFocus && !PickupInFocus->IsPendingKill() && PickupInFocus->IsActive()) {

		//call this version of Collected() as it will capture any Blueprint script we may use to override the function
		PickupInFocus->Collected();

		//turn off postprocessing
		PickupInFocus->SetGlowEffect(false);
		
		//deactivate the item we picked up
		PickupInFocus->SetActive(false);

		//See is there is room in the inventory for more items
		int32 AvailableSpot = Inventory.Find(nullptr);
		
		if (AvailableSpot != INDEX_NONE) {
			Inventory[AvailableSpot] = PickupInFocus;
			PickupInFocus->Destroy();
			NextNearbyPickup();
		} else GLog->Log("You can't carry any more items!");
	}
		
}

void AGame_OneCharacter::ScanForPickups() {

	NearbyItems.Empty();

	//get all overlapping actors and then store than into an array
	TArray<AActor*> PotentialPickupsInRange;
	TArray<APickup*> Temp;
	CollectionSphere->GetOverlappingActors(PotentialPickupsInRange);

	//for each actor that we collect, find which ones are Pickup items and then save them in NearbyItems array 
	for (int32 Item = 0; Item < PotentialPickupsInRange.Num(); ++Item) {

		APickup* const pickup = Cast<APickup>(PotentialPickupsInRange[Item]);

		if (pickup && !pickup->IsPendingKill() && pickup->IsActive()) {
			Temp.Add(pickup);
		}
	}

	NearbyItems = Temp;
	
	if (NearbyItems.Num() == 0) {
		UE_LOG(LogTemp, Warning, TEXT("There was an issue captian"));
		return;
	}

	//Sort NearbyItems array based on distance from the character (Selection Sort)
	int i, j, minIndex;
	APickup* tmp;
	int n = NearbyItems.Num();

	for (i = 0; i < n - 1; i++) {

		minIndex = i;
		for (j = i + 1; j < n; j++)
			if (CalcDistanceBetweenPawnAndActor(Cast<AActor>(NearbyItems[j])) < CalcDistanceBetweenPawnAndActor(Cast<AActor>(NearbyItems[minIndex]))) {
				minIndex = j;
			}

		if (minIndex != i) {
			tmp = NearbyItems[i];
			NearbyItems[i] = NearbyItems[minIndex];
			NearbyItems[minIndex] = tmp;
		}
	}

	for (APickup* item : NearbyItems) {
		UE_LOG(LogTemp, Warning, TEXT("Pickup name: %s"), *item->GetFName().ToString());
	}

	LastItemSeen = PickupInFocus;
	LastItemSeen->SetGlowEffect(false);

	PickupInFocus = NearbyItems[0];

	if (PickupInFocus != nullptr) {
		PickupInFocus->SetGlowEffect(true);
	}
}

void AGame_OneCharacter::NextNearbyPickup() {
	
	if (NearbyItems.Num() <= 1) {
		return;
	}

	PickupInFocus->SetGlowEffect(false);

	int32 n = NearbyItems.Num();

	for (int32 item = 0; item < n; item++) {

		//safety first kids
		if (!NearbyItems.IsValidIndex(item) && (NearbyItems[item] == nullptr)) {
			UE_LOG(LogTemp, Warning, TEXT("There was a issue caption!"));
			continue;
		}

		if ((NearbyItems[item] == PickupInFocus) && ((item + 1) < n)) {
			LastItemSeen = PickupInFocus;
			PickupInFocus = NearbyItems[item + 1];
			PickupInFocus->SetGlowEffect(true);
			break;
		} else if (item + 1 >= n) {
			LastItemSeen = PickupInFocus;
			PickupInFocus = NearbyItems[0];
			PickupInFocus->SetGlowEffect(true);
			break;
		} 
	}

	PickupInFocus->SetGlowEffect(true);
}

void AGame_OneCharacter::MoveRight(float Value) {
	// add movement in that direction
	AddMovementInput(FVector(0.f,-1.f,0.f), Value);
}

void AGame_OneCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location) {
	// jump on any touch
	Jump();
}

void AGame_OneCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}

//called when the level is loaded
void AGame_OneCharacter::BeginPlay()
{
	Super::BeginPlay();

	LastItemSeen = nullptr;
	PickupInFocus = nullptr;
}

//Called very every frame
void AGame_OneCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	//Scan for pickups 
	//ScanForPickups();
	//Raycast();
}

//this allows for us to open and then close the inventory UI screen. Realy just a wrapper that calls the HandleInventoryInput() method
void AGame_OneCharacter::HandleInventoryInput() {
	AMyPlayerController* Controller = Cast<AMyPlayerController>(this->GetController());

	if (Controller) {
		Controller->HandleInventoryInput();
	}
}

//returns current inventory items 
TArray<APickup*> AGame_OneCharacter::GetInventory() {
	return Inventory;
}

//TODO find how to implement the starting and ending locations of the raytrace
void AGame_OneCharacter::Raycast() {
	//FirstPersonCameraComponent->GetComponentLocation();
	//StartLocation + (FirstPersonCameraComponent->GetForwardVector() * RaycastRange);
	
	
	//Calculating start and end location
	FVector StartLocation;
	FVector EndLocation;
 
	FHitResult RaycastHit;
 
	//Raycast should ignore the character
	FCollisionQueryParams CQP;
	CQP.AddIgnoredActor(this);
 
	//Raycast
	GetWorld()->LineTraceSingleByChannel(RaycastHit, StartLocation, EndLocation, ECollisionChannel::ECC_WorldDynamic, CQP);
 
	
	APickup* Pickup = Cast<APickup>(RaycastHit.GetActor());
 
	if (LastItemSeen && LastItemSeen != Pickup)
	{
		//If our character sees a different pickup then disable the glowing effect on the previous seen item
		LastItemSeen->SetGlowEffect(false);
	}
 
	if (Pickup)
	{
		//Enable the glow effect on the current item
		LastItemSeen = Pickup;
		Pickup->SetGlowEffect(true);
	}//Re-Initialize 
	else LastItemSeen = nullptr;

}
