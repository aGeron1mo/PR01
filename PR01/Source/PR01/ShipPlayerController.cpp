// Fill out your copyright notice in the Description page of Project Settings.

#include "PR01.h"
#include "ShipPlayerController.h"


AShip* AShipPlayerController::GetPlayerShip() const
{
	return Cast<AShip>(GetPawn());
}

// Called when the game starts or when spawned
void AShipPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	InputComp = GetWorld()->GetFirstPlayerController()->GetPawn()->FindComponentByClass<UInputComponent>();
	if (InputComp) {
		InputComp->BindAxis(FName(TEXT("AimRoll")), this, &AShipPlayerController::AimThrustRoll);
		InputComp->BindAxis(FName(TEXT("AimYaw")), this, &AShipPlayerController::AimThrustYaw);
		InputComp->BindAxis(FName(TEXT("AimPitch")), this, &AShipPlayerController::AimThrustPitch);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Input component not found"));
	}
	if (GetPlayerShip()) {
		UE_LOG(LogTemp, Warning, TEXT("Get Player Ship %s"), *GetPlayerShip()->GetName());
	}

}

// Called every frame
void AShipPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AShipPlayerController::AimThrustRoll(float val)
{
	GetPlayerShip()->ThrustRollActivate(val);

}

void AShipPlayerController::AimThrustYaw(float val)
{
	GetPlayerShip()->ThrustYawActivate(val);
}

void AShipPlayerController::AimThrustPitch(float val)
{
	GetPlayerShip()->ThrustPitchActivate(val);
}

