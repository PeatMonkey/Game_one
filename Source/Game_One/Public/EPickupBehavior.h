// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EPickupBehavior.generated.h"

/*
	This class enum class is to facilitate the inventory pickup system. The player or some other caller will request activation o
	a pickup or child inventory class. The pickup will return one of the values of the enum to indicate desired behavior.
*/
UENUM(BlueprintType)
enum class EPickupBehavior : uint8
{
	ET_Highlight     UMETA(DisplayName = "Highlight"),
	ET_Remain_Hidden   UMETA(DisplayName = "Keep_Hidden"),
	ET_Indicate_Presence    UMETA(DisplayName = "Indicate_Presence"), 
	ET_Auto_Absorb    UMETA(DisplayName = "Auto_Absorb")
};