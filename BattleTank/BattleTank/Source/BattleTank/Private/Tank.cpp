// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Tank.h"
#include "Public/TankBarrel.h"
#include "Public/TankTurret.h"
#include "Public/Projectile.h"
#include "Engine/World.h"
#include "Public/TankAimingComponent.h"
#include "Public/TankMovementComponent.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UE_LOG(LogTemp, Warning, TEXT("BASTION: Tank Constructor"));
}

void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTime;
	if (Barrel && isReloaded)
		//Spawn a projectile at the barrel' location
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBluePrint,
			Barrel->GetSocketLocation(FName("Projecttile")),
			Barrel->GetSocketRotation(FName("Projecttile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

void ATank::AimAt(FVector HitLocation)
{
	if (!TankAimingComponent) return;
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("BASTION: Tank BeginPlay"));
	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

