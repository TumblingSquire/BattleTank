// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "Tank.h" // For implementation of tank death
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "Public/DrawDebugHelpers.h"



// Sets default values for this component's properties
ATankPlayerController::ATankPlayerController()
{
	// Set this actor to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryActorTick.bCanEverTick = true;
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!(GetPawn())) return;
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(AimingComponent)) return; 
	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardCrosshair();
}

void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) return;

		// subscibe to death event
		PossessedTank->OnTankDeath.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);
	}
}

void ATankPlayerController::AimTowardCrosshair()
{
	if (!GetPawn()) { return; }
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) return;

	FVector HitLocation; // OUT parameter
	// Get Linetrace where it hit the world through the crosshair
	if (GetSightRayHitLocation(HitLocation))
	{
		AimingComponent->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & HitLocation) const
{
	HitLocation = FVector(1.0);
	// find the crosshair position in pixel coordinates
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);

	// convert screen 2D location to the 3D world location
	auto ScreenLocation = FVector2D(ViewPortSizeX * CrossHairXLocation, ViewPortSizeY * CrossHairYLocation);
	FVector CameraWorldDirection, CameraWorldLocation;
	DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		CameraWorldLocation, 
		CameraWorldDirection);

	// Line-trace from this screen location, straight forward along the look direction, max reach.
	return (GetLookVectorHitLocation(HitLocation, CameraWorldLocation, CameraWorldDirection));
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector & HitLocation, 
	FVector CameraWorldLocation, 
	FVector CameraWorldDirection) const
{
	FHitResult HitResult;
	
	/// Ray-casting (Line-tracing)
	if (GetWorld()->LineTraceSingleByChannel(
		OUT HitResult,
		CameraWorldLocation,
		CameraWorldLocation + CameraWorldDirection*LineTraceRange,
		ECollisionChannel::ECC_Camera))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	else
	{
		return false;
	}
	
}

void ATankPlayerController::OnTankDeath()
{
	StartSpectatingOnly();
}
