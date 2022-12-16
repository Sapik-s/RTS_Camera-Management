// Fill out your copyright notice in the Description page of Project Settings.

#include "GenericPlatform/ICursor.h"
#include "GameFramework/PlayerController.h"
#include "PC_MainController.h"

APC_MainController::APC_MainController()
{
	SettingsCursor();
}

void APC_MainController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void APC_MainController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	InputComponent->BindAction("LeftMouseClick", IE_Pressed, this, &APC_MainController::SelectionPressed);
	InputComponent->BindAction("LeftMouseClick", IE_Released, this, &APC_MainController::SelectionReleased);

	InputComponent->BindAction("RightMouseClick", IE_Released, this, &APC_MainController::MoveReleased);
}

void APC_MainController::BeginPlay()
{
	Super::BeginPlay();
	HUDPtr = Cast<AHUD_SelectionUnit>(GetHUD());
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

void APC_MainController::SelectionPressed()
{
	HUDPtr->InitialPoint = HUDPtr->GetMousePosition2D();
	HUDPtr->bStartSelecting = true;
}

void APC_MainController::SelectionReleased()
{
	HUDPtr->bStartSelecting = false;
	SelectedActors = HUDPtr->FoundActors;
}

void APC_MainController::MoveReleased()
{
	if (SelectedActors.Num() > 0)
	{
		for (int32 i = 0; i < SelectedActors.Num(); i++) {
			FHitResult HitResult;
			GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
			FVector MoveLocation = HitResult.Location + FVector(i / 2 * 100, i % 2 * 100, 0);
			//UNavigationSystem::SimpleMoveToLocation(SelectedActors[i]->GetController(), MoveLocation);
			//DrawDebugSphere(GetWorld(), MoveLocation, 25, 10, FColor::Red, 3);
		}
	}
}
