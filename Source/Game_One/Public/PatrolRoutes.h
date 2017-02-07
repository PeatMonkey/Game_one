// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "PatrolRoutes.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAME_ONE_API UPatrolRoutes : public UActorComponent
{
	GENERATED_BODY()

public:
	TArray<AActor *> GetPatrolPoints();
private:
	// Sets default values for this component's properties
	UPROPERTY(EditInstanceOnly, Category = "Patrol Route")
	TArray<AActor *> PatrolPoints;
		
	
};
