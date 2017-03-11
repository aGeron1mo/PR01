// Fill out your copyright notice in the Description page of Project Settings.

#include "PR01.h"
#include "Ship.h"


// Sets default values
AShip::AShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShip::BeginPlay()
{
	Super::BeginPlay();
	
	auto ShipName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("Actor name: %s"), *ShipName);

}

// Called every frame
void AShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Fly();
}

// Called to bind functionality to input
void AShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AShip::SpeedUp()
{
	ShipSpeedUp += 1.f;

	UE_LOG(LogTemp, Warning, TEXT("Speed Up %f"), ShipSpeedUp);

}

void AShip::SpeedDown()
{
	ShipSpeedUp -= 1.f;

	UE_LOG(LogTemp, Warning, TEXT("Speed Down %f"), ShipSpeedUp);

}


void AShip::Fly()
{
	ShipLocation += FVector(0, ShipSpeedUp, 0);
	SetActorLocation(ShipLocation);
}

