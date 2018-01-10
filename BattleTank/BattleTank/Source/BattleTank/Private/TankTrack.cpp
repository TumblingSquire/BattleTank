// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called every frame
void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	auto SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());

	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	auto TankRoot = Cast<UStaticMeshComponent> (GetOwner()->GetRootComponent());

	// divide by 2 for 2 tracks
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2;

	TankRoot->AddForce(CorrectionForce);
}
void UTankTrack::SetThrottle(float Throttle)
{
	// Ensure relative speed does not exceed our MaxDegrees per second
	auto ClampedSpeed = FMath::Clamp<float>(Throttle, -1, 1);

	auto ForceApplied = GetForwardVector() * ClampedSpeed * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
