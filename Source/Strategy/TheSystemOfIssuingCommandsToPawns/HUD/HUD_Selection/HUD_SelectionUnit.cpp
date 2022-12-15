// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD_SelectionUnit.h"

FVector2d AHUD_SelectionUnit::GetMousePosition2D()
{
	float MousePosX;
	float MousePosY;

	GetOwningPlayerController()->GetMousePosition(MousePosX, MousePosY);

	return FVector2d(MousePosX, MousePosY);
}

void AHUD_SelectionUnit::DrawHUD()
{
	if (bStartSelecting)
	{
		CurrentPoint = GetMousePosition2D();
		DrawRect(FLinearColor(0, 0, 1, .15f), InitialPoint.X, InitialPoint.Y, CurrentPoint.X - InitialPoint.X, CurrentPoint.Y - InitialPoint.Y);
	}
	
}
