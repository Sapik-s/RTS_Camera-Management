// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "PawnTank.generated.h"

UCLASS()
class STRATEGY_API APawnTank : public ABasePawn
{
	GENERATED_BODY()
	
public:

	APawnTank();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetSelected();
	void SetDeselected();

protected:

	virtual void BeginPlay() override;

private:

	FVector MoveDirection;
	FQuat RotationDirection;
	
	void CalculateMoveInput(float Value);
	void CalculateRotateInput(float Input);

	void Move();
	void Rotate();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom | Actor Settings | Values | Movement", meta = (AllowPrivateAccess = "true"))
	float MoveSpeed = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom | Actor Settings | Values | Movement", meta = (AllowPrivateAccess = "true"))
	float RotateSpeed = 100.f;
};
