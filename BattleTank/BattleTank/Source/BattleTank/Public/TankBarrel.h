// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS( meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float DegreesPerSecond);
	
private:
	UPROPERTY(EditAnywhere, Category = "Setting")
		float MaxDegreesPerSecond = 20.f;

	UPROPERTY(EditAnywhere, Category = "Setting")
		float MinElevateDegree = 0.f;

	UPROPERTY(EditAnywhere, Category = "Setting")
		float MaxElevateDegree = 40.f;
};
