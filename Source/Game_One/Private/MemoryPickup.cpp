// Fill out your copyright notice in the Description page of Project Settings.

#include "Game_One.h"
#include "MemoryPickup.h"

//set default values
AMemoryPickup::AMemoryPickup() {

	//Following allow the pickup to tick every frame
	SetActorTickEnabled(true);
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.SetTickFunctionEnable(true);
	PrimaryActorTick.bStartWithTickEnabled = true;

	//as soon as the battery is initialized physics propery wil be enabled
	GetMesh()->SetSimulatePhysics(true);

	SplineComp = CreateDefaultSubobject<USplineComponent>(FName(TEXT("SplineComp")), false);

	PickupBehavior = EPickupBehavior::ET_Auto_Absorb;

}

// Called when the game starts or when spawned
void AMemoryPickup::BeginPlay()
{
	Super::BeginPlay();

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

bool AMemoryPickup::ActivatePickup() {
	
	UE_LOG(LogTemp, Warning, TEXT("Pickup event fired!!"));

	SplineComp->SetDrawDebug(true);

	//create our spline curve to follow
	SplineComp->SetWorldLocationAtSplinePoint(0, GetActorLocation());
	SplineComp->SetWorldLocationAtSplinePoint(1, GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation());

	SplineDistance = SplineComp->GetDistanceAlongSplineAtSplinePoint(1);

	bIsMoving = true;

	return true;
}

EPickupBehavior AMemoryPickup::RequestPickup()
{
	return PickupBehavior;
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

		CurrentDistance += MovementSpeed;
		
	}

	if (CurrentDistance >= SplineDistance) {
		UE_LOG(LogTemp, Warning, TEXT("Movement has ended"));
		bIsMoving = false;
		Destroy();
	}
	
	
}