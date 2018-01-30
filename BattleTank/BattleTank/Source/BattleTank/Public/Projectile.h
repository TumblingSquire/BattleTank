// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UStaticMeshComponent;
class UParticleSystemComponent;
class URadialForceComponent;

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void LaunchProjectile(float LaunchSpeed);

private:
	UProjectileMovementComponent * ProjectileMovementComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Destroy")
	float DestroyDelay = 5.f;

	UPROPERTY(VisibleAnywhere, Category = "Particle Effect")
		UStaticMeshComponent * CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Particle Effect")
		UParticleSystemComponent * LaunchBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Particle Effect")
		UParticleSystemComponent * ImpactBlast = nullptr;


	UPROPERTY(VisibleAnywhere, Category = "Particle Effect")
		URadialForceComponent * ExplosionForce = nullptr;

	UFUNCTION(BlueprintCallable, Category = "Collision")
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherCOmponent, FVector NormalImpulse, const FHitResult& Hit);

	FTimerHandle SampleTimerHandle;

	UFUNCTION()
	void OnDestroy();
};
