// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/Actor.h"
#include "PawnTank.h"

APawnTank::APawnTank()
{
	PrimaryActorTick.bCanEverTick = true;
	
}

void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Rotate();
	Move();
}

void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMoveInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateRotateInput);
}

void APawnTank::BeginPlay()
{
	Super::BeginPlay();
}

void APawnTank::CalculateMoveInput(float Value)
{
	MoveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0);	
}

void APawnTank::CalculateRotateInput(float Value)
{
	float RotateAmout = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator Rotation = FRotator(0, RotateAmout, 0);
	RotationDirection = FQuat(Rotation);
}

void APawnTank::Move()
{
	AddActorLocalOffset(MoveDirection, true);
}

void APawnTank::Rotate()
{
	AddActorLocalRotation(FQuat(RotationDirection), true);
}

void APawnTank::SetSelected()
{
	UE_LOG(LogTemp, Warning, TEXT("Actor Selected"));
}

void APawnTank::SetDeselected()
{
	UE_LOG(LogTemp, Warning, TEXT("Actor Deselected"));
}
