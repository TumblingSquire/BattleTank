// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"


// Depending on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	if (!ensure(PlayerPawn && ControlledTank)) return;

	// Move toward the player
	MoveToActor(PlayerPawn, AcceptanceRadius);

	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	auto PlayerTankLocation = PlayerPawn->GetActorLocation();
	AimingComponent->AimAt(PlayerTankLocation);

	AimingComponent->Fire();

}