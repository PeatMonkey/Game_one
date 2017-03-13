// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Game_One.h"
#include "Game_OneGameMode.h"
#include "Game_OneCharacter.h"

AGame_OneGameMode::AGame_OneGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Player/Player_Controllers/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
