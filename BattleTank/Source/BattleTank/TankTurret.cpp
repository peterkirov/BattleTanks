// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed) {
	auto RelSpeedClamped = FMath::Clamp(RelativeSpeed, -1.0f, 1.f);
	auto RotationChange = RelSpeedClamped * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation = GetRelativeRotation().Yaw + RotationChange;
	SetRelativeRotation(FRotator(0,RawNewRotation, 0));
}