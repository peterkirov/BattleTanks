// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

// this is the old code where we clamp the angle parameter and use it as the speed factor
/*
void UTankTurret::Rotate(float RelativeSpeed) {
	auto RelSpeedClamped = FMath::Clamp(RelativeSpeed, -1.0f, 1.f);
	auto RotationChange = RelSpeedClamped * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation = GetRelativeRotation().Yaw + RotationChange;
	SetRelativeRotation(FRotator(0,RawNewRotation, 0));
}
*/


//new code use the parameter as the angle and limit if speed would be exceeded
void UTankTurret::Rotate(float RelativeSpeed) {
	float MaxLimitedAngle = MaxDegreesPerSecond * FMath::Sign(RelativeSpeed) * GetWorld()->DeltaTimeSeconds;
	SetRelativeRotation(FRotator(0.0f,
		FMath::Abs(RelativeSpeed) > FMath::Abs(MaxLimitedAngle) ?
		GetRelativeRotation().Yaw + MaxLimitedAngle :
		GetRelativeRotation().Yaw + RelativeSpeed,
		0.0f));
}