// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"
#include "Public/Tank.h"
#include "Engine/World.h"



ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());

}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI is not possessing any tank."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT(" AI is possing tank: %s"), *ControlledTank->GetName());
	}


	auto PlayerPawn = GetPlayerTank();

	if (!PlayerPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI is not detecting any Player Tank."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI detected Player Tank: %s"), *PlayerPawn->GetName());
	}
}

ATank * ATankAIController::GetPlayerTank() 
{
	auto PlayerPawn = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (!PlayerPawn)
	{
		return nullptr;
	}
	else
	{
		return PlayerPawn;
	}
}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank())
	{
		auto PlayerTankLocation = GetPlayerTank()->GetActorLocation();
		GetControlledTank()->AimAt(PlayerTankLocation);
	}
}