// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be the last include

class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* AimCompRef);

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

	UPROPERTY(EditAnywhere, Category = "UISetting")
		float CrossHairXLocation = .5f;

	UPROPERTY(EditAnywhere, Category = "UISetting")
		float CrossHairYLocation = .3333f;

	UPROPERTY(EditAnywhere, Category = "UISetting")
	float LineTraceRange = 50000.f;

};
