// Copyright Epic Games, Inc. All Rights Reserved.

#include "Player_Controllers/PC_MainController.h"
#include "StrategyGameModeBase.h"

AStrategyGameModeBase::AStrategyGameModeBase()
{
	DefaultPawnClass = nullptr;

	PlayerControllerClass = APC_MainController::StaticClass();

}
