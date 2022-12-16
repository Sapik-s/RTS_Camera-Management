// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include <Strategy/Pawns/PawnTank.h>
#include "HUD_SelectionUnit.generated.h"

UCLASS()
class STRATEGY_API AHUD_SelectionUnit : public AHUD
{
	GENERATED_BODY()
	
public:
	bool bStartSelecting = false;

	FVector2d InitialPoint;
	FVector2d CurrentPoint;

	FVector2d GetMousePosition2D();

	TArray<APawnTank*> FoundActors;

	virtual void DrawHUD() override;
};
