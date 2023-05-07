// Copyright Epic Games, Inc. All Rights Reserved.

#include "PDP_TasksGameMode.h"
#include "PDP_TasksCharacter.h"
#include "UObject/ConstructorHelpers.h"

APDP_TasksGameMode::APDP_TasksGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
