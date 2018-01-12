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
	UTankTrack();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);

	void DriveTrack();

	// Force of each trach, in Newton
	// Assuming tank goes faster here than in real life, being 10m/s², reaching 100meter/second in 10seconds
	// And tank weights at 40 tons, or 40,000 kilograms 
	// Force = Mass * Acceleration;
	UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingForce = 46000000.f;

private:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ApplySidewayForce();

	UFUNCTION(BlueprintCallable, Category = "Collision")
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherCOmponent, FVector NormalImpulse, const FHitResult& Hit);

	float CurrentThrottle = 0.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
