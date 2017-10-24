// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
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
	auto ControlledTank = GetControlledTank();

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player is not possessing any tank."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player is possessing tank: %s"), *ControlledTank->GetName());
	}

	
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardCrosshair();
}

void ATankPlayerController::AimTowardCrosshair()
{
	if (!GetControlledTank()) return;

	FVector HitLocation; // OUT parameter
	// Get Linetrace where it hit the world through the crosshair
	if (GetSightRayHitLocation(HitLocation))
	{

		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & HitLocation) const
{
	HitLocation = FVector(1.0);
	return true;
}

const FHitResult ATankPlayerController::GetWorldPointCollideWithCrosshair() 
{
	FHitResult HitResult;

	/// Setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	/// Ray-casting (Line-tracing)
	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		GetLineTraceStart(),
		GetLineTraceEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic),
		TraceParameters
	);
	return HitResult;
}
FVector ATankPlayerController::GetLineTraceEnd()
{
	// Get player's view point this tick
	GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}

FVector ATankPlayerController::GetLineTraceStart()
{
	return PlayerViewPointLocation;
}