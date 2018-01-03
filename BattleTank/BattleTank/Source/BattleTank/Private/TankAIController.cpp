// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"
#include "Public/Tank.h"
#include "Engine/World.h"


// Depending on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto PlayerPawn = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());

	if (ensure(PlayerPawn))
	{
		// Move toward the player
		MoveToActor(PlayerPawn, AcceptanceRadius);

		auto PlayerTankLocation = PlayerPawn->GetActorLocation();
		ControlledTank->AimAt(PlayerTankLocation);

		ControlledTank->Fire();
	}
}