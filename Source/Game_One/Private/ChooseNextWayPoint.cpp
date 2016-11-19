// Fill out your copyright notice in the Description page of Project Settings.

#include "Game_One.h"
#include "ChooseNextWayPoint.h"
#include "AIController.h"
#include "PatrollingGuard.h" //TODO remove this later
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UChooseNextWayPoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	using namespace EBTNodeResult;
	
	//get the patrol points
	auto AIController = OwnerComp.GetAIOwner();
	auto GetControlledPawn = AIController->GetPawn();
	auto PatrollingGaurd = Cast<APatrollingGuard>(GetControlledPawn);
	auto PatrolPoints = PatrollingGaurd->GetPatrolPoints();

	//Set the next waypoint
	auto BlackBoardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackBoardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackBoardComp->SetValueAsObject(WayPointKey.SelectedKeyName, PatrolPoints[Index]);

	//Cycle the Index
	auto NextIndex = (Index + 1) % PatrolPoints.Num();
	BlackBoardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);
	
	return Succeeded;
	
}
