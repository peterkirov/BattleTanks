// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto controlledTank = GetControlledTank();
	if (!controlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possesing a tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possesing %s"), *(controlledTank->GetName()));
	}
	UE_LOG(LogTemp, Warning, TEXT("PlayerController BeginPlay"));
}


//Tick
	// Super
	// AimTowardsCrosshair

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
	
	//UE_LOG(LogTemp, Warning, TEXT("yup"));
}



ATank* ATankPlayerController::GetControlledTank() const {

	return Cast<ATank>(GetPawn());
	

}

void ATankPlayerController::AimTowardsCrosshair() const
{
	auto controlledTank = GetControlledTank();
	if (!controlledTank) {
		return;
	}
	
	
	FVector HitLocation; // Out parameter
	if (GetSightRayHitLocation(HitLocation)) // Has "side-effect", is going to line trace
	{
		// TODO Tell controlled tank to aim at this point
		GetControlledTank()->AimAt(HitLocation);
	}
	GetControlledTank()->AimAt(HitLocation);
}

// Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	//Find the crosshair position
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);
	auto ScreenLocation = FVector2D(ViewPortSizeX * CrossHairXLocation, ViewPortSizeY * CrossHairYLocation);

	FVector LookDirection;
	//"De-project" the screen position of the crosshair to a world direction
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		//line trace along that look direction see what we hit (up to max range)
		if (GetLookVectorHitDirection(LookDirection, HitLocation)) {
			return true;
		}

	}
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const {
	FVector cameraWorldLocation;//to be discarded
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		cameraWorldLocation, 
		LookDirection);
}

bool ATankPlayerController::GetLookVectorHitDirection(FVector LookDirection, FVector& HitLocation) const{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility)
		) {
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;
}