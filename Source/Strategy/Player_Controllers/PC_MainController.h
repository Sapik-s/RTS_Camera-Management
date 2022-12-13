// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PC_MainController.generated.h"

UCLASS()
class STRATEGY_API APC_MainController : public APlayerController
{
	GENERATED_BODY()

public:

	APC_MainController();

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

private:
	bool ShowMouseCursor = true;

	void SettingsCursor();
};
