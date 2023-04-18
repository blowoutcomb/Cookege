// Copyright Epic Games, Inc. All Rights Reserved.

#include "cookinguyGameMode.h"
#include "cookinguyCharacter.h"
#include "UObject/ConstructorHelpers.h"

AcookinguyGameMode::AcookinguyGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
