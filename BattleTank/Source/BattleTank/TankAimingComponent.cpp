// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;//TODO should this really tick

	// ...
}




void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	Turret = TurretToSet;
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {
	auto OutTankName = GetOwner()->GetName();
	auto BarrelLocation = Barrel->GetComponentLocation();
	//UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), *OutTankName, *HitLocation.ToString(), *BarrelLocation.ToString());

	if (!Barrel) {
		return;
	}
	FVector OutLaunchVelocity = FVector(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	//calculate the outlaunch velocity
	
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	
	/*const TArray<AActor*> ActorsToIgnore;
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		BarrelLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::TraceFullPath,
		FCollisionResponseParams::DefaultResponseParam,
		ActorsToIgnore,
		true
	);*/
	if (bHaveAimSolution) 
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: aim solution found %s"), Time, *OutTankName);
		MoveBarrel(AimDirection);
		MoveTurret(AimDirection);
	}
	else {
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: no aim solve found %s"), Time, *OutTankName);
	}
	//if nothing found do nothing


}


void UTankAimingComponent::MoveBarrel(FVector AimDirection) {
	// take the aim direction and move the barrel
	// work out difference between current barrel rotation and aim direction 
	// and then move the barrel the right amount
	// this frame given a max elevation speed, and the frame time
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	
	Barrel->Elevate(DeltaRotator.Pitch); // TODO remove magic number
	
}

void UTankAimingComponent::MoveTurret(FVector AimDirection)
{
}
