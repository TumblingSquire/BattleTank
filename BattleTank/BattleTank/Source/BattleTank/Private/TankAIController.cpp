// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "Tank.h" // For implementation of tank death
#include "Runtime/Engine/Classes/GameFramework/Pawn.h"


// Depending on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!GetWorld()->GetFirstPlayerController()->GetPawn()) { return; }
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	if (!ensure(PlayerPawn && ControlledTank)) return;

	// Move toward the player
	MoveToActor(PlayerPawn, AcceptanceRadius);

	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	auto PlayerTankLocation = PlayerPawn->GetActorLocation();
	AimingComponent->AimAt(PlayerTankLocation);

	if(AimingComponent->GetCurrentFiringStatus() == EFiringStatus::Locked)
		AimingComponent->Fire();

}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) return;

		// subscibe to death event
		PossessedTank->OnTankDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	}
}

void ATankAIController::OnTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("%s acknowledged tank's death."), *GetName());

	if (!(GetPawn())) return;
	GetPawn()->DetachFromControllerPendingDestroy();
}
