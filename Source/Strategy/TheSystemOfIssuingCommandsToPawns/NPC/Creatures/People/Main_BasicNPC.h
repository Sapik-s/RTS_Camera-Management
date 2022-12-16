// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Main_BasicNPC.generated.h"

UCLASS()
class STRATEGY_API AMain_BasicNPC : public ACharacter
{
	GENERATED_BODY()

public:
	AMain_BasicNPC();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
