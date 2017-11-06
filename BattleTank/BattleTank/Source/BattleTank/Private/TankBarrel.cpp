// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankBarrel.h"
#include "Engine/World.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	// Ensure relative speed does not exceed our MaxDegrees per second
	auto ClampedSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);

	// Get degree should be at this time
	auto ElevationChange = ClampedSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

	// Add it to original pitch angle
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	// this Raw elevation should not exceed our exposed min and max angle
	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevateDegree, MaxElevateDegree);

	SetRelativeRotation(FRotator(Elevation, 0, 0));
}


