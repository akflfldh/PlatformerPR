// Copyright Epic Games, Inc. All Rights Reserved.

#include "PlatfomerPRGameMode.h"
#include "PlatfomerPRCharacter.h"
#include "UObject/ConstructorHelpers.h"

APlatfomerPRGameMode::APlatfomerPRGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
