// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Public/Tank.h"
#include "Engine/World.h"
#include "Public/DrawDebugHelpers.h"



// Sets default values for this component's properties
ATankPlayerController::ATankPlayerController()
{
	// Set this actor to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryActorTick.bCanEverTick = true;
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());

}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(AimingComponent)) return;
	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardCrosshair();
}

void ATankPlayerController::AimTowardCrosshair()
{
	if (!(GetControlledTank())) return;

	FVector HitLocation; // OUT parameter
	// Get Linetrace where it hit the world through the crosshair
	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
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
		ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	else
	{
		return false;
	}
	
}