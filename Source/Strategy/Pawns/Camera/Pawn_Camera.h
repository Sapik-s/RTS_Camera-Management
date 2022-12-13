// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Pawn_Camera.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class STRATEGY_API APawn_Camera : public APawn
{
	GENERATED_BODY()

public:
	APawn_Camera();
	
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	//---------------------VALUES---------------------//
	//Отступы
	float Margin = 10.f;
	float MarginX;
	float MarginY;

	float BindKeyValueHoriz;
	float BindKeyValueVertic;

	float SpeedZoomCamera = 15.f;
	float MovementSpeedCamera = 70.f;

	//Положение мыши на экране
	float MousePosX;
	float MousePosY;

	bool bClickMiddleMouse = false;

	//Разрешение монитора
	int32 ScreenSizeX;
	int32 ScreenSizeY;

	FQuat RotateSpringArm;

	FVector GetCameraPosition;
	FVector MoveDirectionX;
	FVector MoveDirectionY;
	FVector MoveDirectionPressedX;
	FVector MoveDirectionPressedY;

	//---------------------UPROPERTY---------------------//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom | Actor Settings | Camera | Values", meta = (AllowPrivateAccess = "true"))
	float CameraFlightAltitude = 2500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom | Actor Settings | Camera | Values", meta = (AllowPrivateAccess = "true"))
	FRotator RotationSpringArm = FRotator(-50.f, -45.f, 0.f);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom | Actor Settings | Camera", meta = (AllowPrivateAccess = "true"))
	USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom | Actor Settings | Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom | Actor Settings | Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	APlayerController* PlayerController;

	//---------------------FUNCTIONS---------------------//
	FVector GetCameraPanDirection();

	void SetInitPlayerController();

	void KeyMoveY(float Value);
	void KeyMoveX(float Value);

	void MiddleMouseX(float Value);
	void MiddleMouseY(float Value);
	void StartMiddleMouse();
	void StopMiddleMouse();

	void ZoomCamera(float Value);

	void MoveCamera();
};