// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed) {
	
	//auto RelSpeedClamped = FMath::Clamp(RelativeSpeed, -1.0f, 1.f);
	//auto ElevationChange = RelSpeedClamped * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	//auto RawNewElevation = GetRelativeRotation().Pitch + ElevationChange;
	//	//RelativeRotation.Pitch + ElevationChange;
	//auto elevation = FMath::Clamp(RawNewElevation, MinElevation, MaxElevation);
	//SetRelativeRotation(FRotator(elevation, 0, 0));

	float MaxLimitedAngle = MaxDegreesPerSecond * FMath::Sign(RelativeSpeed) * GetWorld()->DeltaTimeSeconds;
	float RawNewElevation = FMath::Abs(RelativeSpeed) > FMath::Abs(MaxLimitedAngle) ?
		GetRelativeRotation().Pitch + MaxLimitedAngle :
		GetRelativeRotation().Pitch + RelativeSpeed;
	SetRelativeRotation(FRotator(FMath::Clamp(RawNewElevation, MinElevation, MaxElevation), 0.0f, 0.0f));

}