// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Projectile.h"
#include "PhysicsEngine/PhysicsThrusterComponent.h"
#include "GameFramework/Pawn.h"
#include "Ship.generated.h"

UCLASS()
class PR01_API AShip : public APawn
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this pawn's properties
	AShip();

//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ship")
//		class UPhysicsThrusterComponent* ThrusterTEMP;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void ThrustRollActivate(float val);
	void ThrustYawActivate(float val);
	void ThrustPitchActivate(float val);
	void ThrustEngineActivate(float val);

	void FirePrimary(float val);
	void Boost();

private:
	UPROPERTY(EditAnywhere, Category = "Ship Setup")
		float ThrustRollStrength = 30000;
	UPROPERTY(EditAnywhere, Category = "Ship Setup")
		float ThrustYawStrength = 30000;
	UPROPERTY(EditAnywhere, Category = "Ship Setup")
		float ThrustPitchStrength = 30000;
	UPROPERTY(EditAnywhere, Category = "Ship Setup")
		float EnginePower = 30000;
	UPROPERTY(EditAnywhere, Category = "Ship Setup")
		float BurstPower = 50000000;
	UPROPERTY(EditAnywhere, Category = "Ship Setup")
		UClass* Projectile_BluePrint;

	float ProjectileTimeReloadInSec = 0.2;
	double ProjectileLastFireTime = 0;

	float current_engine_val = 0; // 0 - 100 % power

	UPhysicsThrusterComponent* RightWingRollThrust = nullptr; 
	UPhysicsThrusterComponent* LeftWingRollThrust = nullptr; 
	UPhysicsThrusterComponent* NosePitchThrust = nullptr; 
	UPhysicsThrusterComponent* NoseYawThrust = nullptr;
	UPhysicsThrusterComponent* TailPitchThrust = nullptr;
	UPhysicsThrusterComponent* TailYawThrust = nullptr;

	UArrowComponent* RootDirectionArrow = nullptr;
	UStaticMeshComponent* ShipMainSM = nullptr;

	void SetupEngines();

	FVector ShipLocation;

	void Fly();


	
};
