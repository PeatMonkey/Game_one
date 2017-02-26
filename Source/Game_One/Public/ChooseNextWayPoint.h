// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "ChooseNextWayPoint.generated.h"

/**
 * 
 */
UCLASS()

//Will be a behavior tree task that will show up in "Behavioral tree Editor" in unreal and will allow cycling between blackboard-key "Waypoints" based on their index
class GAME_ONE_API UChooseNextWayPoint : public UBTTaskNode
{
public:
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
private:
	
protected:
	UPROPERTY(EditInstanceOnly, Category = "Blackboard")
	struct FBlackboardKeySelector IndexKey;

	UPROPERTY(EditInstanceOnly, Category = "Blackboard")
	struct FBlackboardKeySelector WaypointKey;
};