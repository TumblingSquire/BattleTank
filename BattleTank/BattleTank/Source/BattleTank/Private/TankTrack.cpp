// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankTrack.h"


void UTankTrack::SetThrottle(float Throttle)
{
	// Ensure relative speed does not exceed our MaxDegrees per second
	auto ClampedSpeed = FMath::Clamp<float>(Throttle, -1, 1);

	auto ForceApplied = GetForwardVector() * ClampedSpeed * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
