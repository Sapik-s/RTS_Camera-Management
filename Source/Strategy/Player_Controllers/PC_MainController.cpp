// Fill out your copyright notice in the Description page of Project Settings.

#include "GenericPlatform/ICursor.h"
#include "PC_MainController.h"

APC_MainController::APC_MainController()
{
	SettingsCursor();
}

void APC_MainController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void APC_MainController::BeginPlay()
{
	Super::BeginPlay();
	
}

void APC_MainController::SettingsCursor()
{
	if (ShowMouseCursor)
	{
		bShowMouseCursor = true;
		bEnableClickEvents = true;
		DefaultMouseCursor = EMouseCursor::Hand;
	}
	else {
		bShowMouseCursor = false;
		bEnableClickEvents = false;
	}
}
