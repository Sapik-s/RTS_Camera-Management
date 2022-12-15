// Copyright Epic Games, Inc. All Rights Reserved.

#include "Player_Controllers/PC_MainController.h"
#include "TheSystemOfIssuingCommandsToPawns/HUD/HUD_Selection/HUD_SelectionUnit.h"
#include "StrategyGameModeBase.h"

AStrategyGameModeBase::AStrategyGameModeBase()
{
	DefaultPawnClass = nullptr;
	HUDClass = AHUD_SelectionUnit::StaticClass();
	PlayerControllerClass = APC_MainController::StaticClass();
}
