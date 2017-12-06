// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankMovementComponent.h"
#include "Public/TankTrack.h"


void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) return;

	RightTrack->SetThrottle(Throw);
	LeftTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) return;

	RightTrack->SetThrottle(Throw);
	LeftTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	// No Super call, we are replacing the functionality
	auto TankName = GetOwner()->GetName();
	auto TankForwardDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto TankIntentionDirection = MoveVelocity.GetSafeNormal();

	IntendTurnRight(FVector::CrossProduct(TankIntentionDirection,TankForwardDirection ).Z);
	IntendMoveForward(FVector::DotProduct(TankForwardDirection, TankIntentionDirection));
}

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

