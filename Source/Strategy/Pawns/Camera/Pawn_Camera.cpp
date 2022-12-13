// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "Pawn_Camera.h"

APawn_Camera::APawn_Camera()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = RootComp;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	SpringArm->SetupAttachment(RootComp);

	SpringArm->SetRelativeRotation(FQuat(RotationSpringArm));
	SpringArm->TargetArmLength = CameraFlightAltitude;

	SpringArm->bDoCollisionTest = false;
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	Camera->SetupAttachment(SpringArm);
}

void APawn_Camera::BeginPlay()
{
	Super::BeginPlay();

	SetInitPlayerController();
}

void APawn_Camera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveCamera();
}

//Бинд клавиш для перемещения камеры.
void APawn_Camera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APawn_Camera::KeyMoveY);
	PlayerInputComponent->BindAxis("Turn", this, &APawn_Camera::KeyMoveX);

	PlayerInputComponent->BindAxis("TurnCameraX", this, &APawn_Camera::MiddleMouseX);
	PlayerInputComponent->BindAxis("TurnCameraY", this, &APawn_Camera::MiddleMouseY);
	PlayerInputComponent->BindAction("TouchMiddleMouse", IE_Pressed, this, &APawn_Camera::StartMiddleMouse);
	PlayerInputComponent->BindAction("TouchMiddleMouse", IE_Released, this, &APawn_Camera::StopMiddleMouse);

	PlayerInputComponent->BindAxis("ZoomCamera", this, &APawn_Camera::ZoomCamera);
}

//Рассчёт скорости и направления смещения камеры при наведения мышкой на границы вьюпорта.
FVector APawn_Camera::GetCameraPanDirection()
{
	float CameraDirectionX = 0;
	float CameraDirectionY = 0;

	MarginX = ScreenSizeX - Margin;
	MarginY = ScreenSizeY - Margin;

	float PositiveValues = 15.f;
	float NegativeValues = -15.f;

	float DiagonalPosValues = 25.f;
	float DiagonalNegValues = -25.f;

	PlayerController->GetMousePosition(MousePosX, MousePosY);

	//Перемещение камеры влево.
	if (MousePosX <= Margin && MousePosY >= Margin && MousePosY <= MarginY)
	{
		CameraDirectionX = NegativeValues;
		CameraDirectionY = NegativeValues;
	}
	//Перемещение камеры вверх.
	if (MousePosY <= Margin && MousePosX >= Margin && MousePosX <= MarginX)
	{
		CameraDirectionX = PositiveValues;
		CameraDirectionY = NegativeValues;
	}
	//Перемещение камеры вправо.
	if (MousePosX >= MarginX && MousePosY >= Margin && MousePosY <= MarginY)
	{
		CameraDirectionX = PositiveValues;
		CameraDirectionY = PositiveValues;
	}
	//Перемещение камеры вниз.
	if (MousePosY >= MarginY && MousePosX >= Margin && MousePosX <= MarginX)
	{
		CameraDirectionX = NegativeValues;
		CameraDirectionY = PositiveValues;
	}

	//Перемещение камеры в левый верхний угол.
	if (MousePosY <= Margin && MousePosX <= Margin)
	{
		CameraDirectionY = DiagonalNegValues;
	}
	//Перемещение камеры в правый верхний угол.
	if (MousePosX >= MarginX && MousePosY <= Margin)
	{
		CameraDirectionX = DiagonalPosValues;
	}
	//Перемещение камеры в правый нижний угол.
	if (MousePosX >= MarginX && MousePosY >= MarginY)
	{
		CameraDirectionY = DiagonalPosValues;
	}
	//Перемещение камеры в левый нижний угол.
	if (MousePosX <= Margin && MousePosY >= MarginY) {
		CameraDirectionX = DiagonalNegValues;
	}

	return FVector(CameraDirectionX, CameraDirectionY, 0);
}

void APawn_Camera::SetInitPlayerController()
{
	PlayerController = Cast<APlayerController>(GetController());
	PlayerController->GetViewportSize(ScreenSizeX, ScreenSizeY);
}

//Рассчёт скорости вертикального перемещения клавишами W и S.
void APawn_Camera::KeyMoveY(float Value)
{
	if (PlayerController->IsInputKeyDown("A") || PlayerController->IsInputKeyDown("D"))
	{
		MoveDirectionY = FVector(Value * 10.f, -Value * 10.f, 0);
	}
	else {
		MoveDirectionY = FVector(Value * 15.f, -Value * 15.f, 0);
	}
}

//Рассчёт скорости горизонтального перемещения клавишами A и D.
void APawn_Camera::KeyMoveX(float Value)
{
	if (PlayerController->IsInputKeyDown("W") || PlayerController->IsInputKeyDown("S"))
	{
		MoveDirectionX = FVector(Value * 10.f, Value * 10.f, 0);
	}
	else {
		MoveDirectionX = FVector(Value * 15.f, Value * 15.f, 0);
	}
}

void APawn_Camera::MiddleMouseX(float Value)
{
	MoveDirectionPressedX = FVector(Value, Value, 0);
}

void APawn_Camera::MiddleMouseY(float Value)
{
	MoveDirectionPressedY = FVector(-Value, Value, 0);
}

void APawn_Camera::StartMiddleMouse() {
	bClickMiddleMouse = true;
}

void APawn_Camera::StopMiddleMouse() {
	bClickMiddleMouse = false;
}

void APawn_Camera::ZoomCamera(float Value) {

	float NextCameraPosition = Value * SpeedZoomCamera * SpringArm->TargetArmLength;
	float NewZoomPosition = NextCameraPosition + SpringArm->TargetArmLength;
	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, FMath::Clamp(NewZoomPosition, 1000, CameraFlightAltitude), GetWorld()->DeltaTimeSeconds, 10.f);
}

void APawn_Camera::MoveCamera()
{
	if (!bClickMiddleMouse && MoveDirectionY == FVector(0, 0, 0) && MoveDirectionX == FVector(0, 0, 0))
	{
		AddActorWorldOffset(GetCameraPanDirection() * MovementSpeedCamera * GetWorld()->DeltaTimeSeconds);
	}
	
	if (!bClickMiddleMouse)
	{
		//Вертикальное перемещение клавишами W и S.
		AddActorWorldOffset(MoveDirectionY * MovementSpeedCamera * GetWorld()->DeltaTimeSeconds);
		//Горизонтальное перемещение клавишами A и D.
		AddActorWorldOffset(MoveDirectionX * MovementSpeedCamera * GetWorld()->DeltaTimeSeconds);
	}
	
	if (bClickMiddleMouse)
	{
		//Вертикальное перемещение средней кнопкой мыши
		AddActorLocalOffset(-(MoveDirectionPressedX) * 35.f * MovementSpeedCamera * GetWorld()->DeltaTimeSeconds);
		//Горизонтальное перемещение средней кнопкой мыши
		AddActorLocalOffset(MoveDirectionPressedY * 35.f * MovementSpeedCamera * GetWorld()->DeltaTimeSeconds);
	}
}