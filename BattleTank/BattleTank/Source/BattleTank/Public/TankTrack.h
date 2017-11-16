// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);
	
	// Force of each trach, in Newton
	// Assuming tank goes faster here than in real life, being 10m/s², reaching 100meter/second in 10seconds
	// And tank weights at 40 tons, or 40,000 kilograms 
	// Force = Mass * Acceleration;
	UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingForce = 400000.f;
};
