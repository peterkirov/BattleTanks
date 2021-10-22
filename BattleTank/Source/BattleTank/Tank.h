// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//forward declarations
class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

private:
	// Sets default values for this pawn's properties
	ATank();

	
	// Called to bind functionality to input
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UTankBarrel* Barrel = nullptr;//local barrel reference to spawn projectile


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UTankAimingComponent* TankAimingComponent = nullptr;

public:	
	

	

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Fire();
	
	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 4000;

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint; 


	void AimAt(FVector HitLocation);

};
