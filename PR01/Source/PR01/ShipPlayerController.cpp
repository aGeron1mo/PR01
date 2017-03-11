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
		InputComp->BindAction(FName(TEXT("Accelerator")), EInputEvent::IE_Repeat, this, &AShipPlayerController::AimAccelerate);
		InputComp->BindAction(FName(TEXT("Decelerator")), EInputEvent::IE_Repeat, this, &AShipPlayerController::AimDecelerate);
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

void AShipPlayerController::AimAccelerate()
{
	GetPlayerShip()->SpeedUp();
}

void AShipPlayerController::AimDecelerate()
{
	GetPlayerShip()->SpeedDown();
}
