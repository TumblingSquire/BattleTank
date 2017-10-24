// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Public/Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be the last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATankPlayerController();

	ATank* GetControlledTank() const;
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
private:
	// start moving barrel to prepare to fire toward the crosshair
	void AimTowardCrosshair();

	// return true if hit landscape
	bool GetSightRayHitLocation(FVector & HitLocation) const;

	const FHitResult GetWorldPointCollideWithCrosshair() ;

	FVector GetLineTraceEnd() ;
	FVector GetLineTraceStart() ;
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	float Reach = 10000.f;

};
