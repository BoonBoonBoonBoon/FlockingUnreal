// Copyright Epic Games, Inc. All Rights Reserved.

#include "FlockingGameMode.h"
#include "FlockingCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFlockingGameMode::AFlockingGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
