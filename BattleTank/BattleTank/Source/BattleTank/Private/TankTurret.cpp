// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankTurret.h"
#include "Engine/World.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	// Ensure relative speed does not exceed our MaxDegrees per second
	auto ClampedSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);

	// Get degree should be at this time
	auto RotationChange = ClampedSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

	// Add it to original pitch angle
	auto RawNewRotation = RelativeRotation.Yaw + RotationChange;

	// this Raw elevation should not exceed our exposed min and max angle
	//auto Rotation = FMath::Clamp<float>(RawNewElevation, MinElevateDegree, MaxElevateDegree);

	SetRelativeRotation(FRotator(0, RawNewRotation, 0));
	//UE_LOG(LogTemp, Warning, TEXT(" Barrel Rotating by: %f "), RawNewRotation);
}


