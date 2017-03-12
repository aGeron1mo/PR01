// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Ship.h"
#include "GameFramework/PlayerController.h"
#include "ShipPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PR01_API AShipPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	AShip* GetPlayerShip() const;
	virtual void Tick(float DeltaTime) override;	

private:

	void AimAccelerate();
	void AimDecelerate();
	void ThrustRoll();

	UInputComponent* InputComp = nullptr;


};
