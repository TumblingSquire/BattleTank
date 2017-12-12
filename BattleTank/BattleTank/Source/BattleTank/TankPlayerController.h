// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be the last include

class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
		ATank* GetControlledTank() const;

private:
	ATankPlayerController();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	// start moving barrel to prepare to fire toward the crosshair
	void AimTowardCrosshair();

	// return true if hit landscape
	bool GetSightRayHitLocation(FVector & HitLocation) const;

	bool GetLookVectorHitLocation(FVector & HitLocation, FVector CameraWorldLocation,
		FVector CameraWorldDirection) const;

	UPROPERTY(EditAnywhere)
		float CrossHairXLocation = .5f;

	UPROPERTY(EditAnywhere)
		float CrossHairYLocation = .3333f;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 50000.f;

};
