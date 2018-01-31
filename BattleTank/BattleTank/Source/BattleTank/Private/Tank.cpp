// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Tank.h"
#include "Engine/World.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
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

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth/(float)MaxHealth;
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagaPoint = FPlatformMath::RoundToInt(DamageAmount);
	// Ensure damage does not exceed our current health
	int32 FinalDamageAmount = FMath::Clamp<int32>(DamagaPoint, 0, CurrentHealth);

	CurrentHealth -= FinalDamageAmount;

	if (CurrentHealth <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("(HP %i/%i) %s takes %i amount of damage (%i when full)"), CurrentHealth, MaxHealth, *GetName(), FinalDamageAmount, DamagaPoint);

	}
	return FinalDamageAmount;
}

