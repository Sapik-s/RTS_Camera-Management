// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "../TheSystemOfIssuingCommandsToPawns/HUD/HUD_Selection/HUD_SelectionUnit.h"
#include "PC_MainController.generated.h"

UCLASS()
class STRATEGY_API APC_MainController : public APlayerController
{
	GENERATED_BODY()

public:

	APC_MainController();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	AHUD_SelectionUnit* HUDPtr;

protected:

	virtual void BeginPlay() override;

	bool ShowMouseCursor = true;

	void SettingsCursor();
	
	void SelectionPressed();
	void SelectionReleased();
	void MoveReleased();
};
