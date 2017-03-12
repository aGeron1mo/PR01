// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ship Setup")
		class UPhysicsThrusterComponent* ThrusterTEMP;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SpeedUp();
	void SpeedDown();
	void ThrustRightWindRollActivate();
	void ThrustLeftWindRollActivate();

private:

	// Сила движков для ROLL (На крыльях корабля)
	UPROPERTY(EditAnywhere, Category = "Ship Setup")
		float ThrustRollStrength = 100000;

	UActorComponent* RightThruster = nullptr; // Правый трастовый двигатель 
	UPhysicsThrusterComponent* LeftThruster = nullptr; // Левый трастовый двигатель 

	FVector ShipLocation;

	float ShipSpeedUp = 0.f;
	void Fly();


	
};
