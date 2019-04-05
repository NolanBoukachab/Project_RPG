// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "LowPoly_WorldGameMode.h"
#include "LowPoly_WorldCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALowPoly_WorldGameMode::ALowPoly_WorldGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
