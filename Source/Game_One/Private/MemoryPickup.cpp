// Fill out your copyright notice in the Description page of Project Settings.

#include "Game_One.h"
#include "MemoryPickup.h"

//set default values
AMemoryPickup::AMemoryPickup() {

	SetActorTickEnabled(true);
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.SetTickFunctionEnable(true);
	PrimaryActorTick.bStartWithTickEnabled = true;

	//as soon as the battery is initialized physics propery wil be enabled
	GetMesh()->SetSimulatePhysics(true);
	//FObjectInitializer* ObjectInitializer = new FObjectInitializer();

	SplineComp = CreateDefaultSubobject<USplineComponent>(FName(TEXT("SplineComp")), false);

}

// Called when the game starts or when spawned
void AMemoryPickup::BeginPlay()
{
	Super::BeginPlay();

}

void AMemoryPickup::Collected_Implementation() {
	// use the base pickup behavior
	Super::Collected_Implementation();

	//get ride of the item after the pickup
	//Destroy();
}

// Called every frame
void AMemoryPickup::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);
	
	if (bIsMoving) {
		UE_LOG(LogTemp, Warning, TEXT("Moving"));
		MoveTowards();
	} 
}

bool AMemoryPickup::CollectPickup() {
	
	UE_LOG(LogTemp, Warning, TEXT("Pickup event fired!!"));

	SplineComp->SetDrawDebug(true);

	//create our spline curve to follow
	SplineComp->SetWorldLocationAtSplinePoint(0, GetActorLocation());
	SplineComp->SetWorldLocationAtSplinePoint(1, GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation());

	SplineDistance = SplineComp->GetDistanceAlongSplineAtSplinePoint(1);

	bIsMoving = true;

	return true;
}

void AMemoryPickup::MoveTowards() {

	if (GetWorld()->GetFirstPlayerController()->GetPawn() != nullptr) { 

		//gives us the world location were are at a particular distance on the spline
		CurrentLocation = SplineComp->GetWorldLocationAtDistanceAlongSpline(CurrentDistance);

		//Given a distance along the length of this spline, return a rotation corresponding to the spline's rotation there, in world space.
		CurrentRotation = SplineComp->GetWorldRotationAtDistanceAlongSpline(CurrentDistance);

		FHitResult* Obstruction = new FHitResult();

		SetActorRotation(CurrentRotation, ETeleportType::None);
		SetActorLocation(CurrentLocation, false, Obstruction, ETeleportType::None);

		CurrentDistance += 20;
		
	}

	if (CurrentDistance >= SplineDistance) {
		UE_LOG(LogTemp, Warning, TEXT("Movement has ended"));
		bIsMoving = false;
		Destroy();
	}
	
	
}