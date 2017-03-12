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

	SetupThrusters();
}

// Called every frame
void AShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void AShip::ThrustRollActivate(float val)
{
	RightWingRollThrust->Activate(true);
	LeftWingRollThrust->Activate(true);
	RightWingRollThrust->ThrustStrength = ThrustRollStrength * val;
	LeftWingRollThrust->ThrustStrength = ThrustRollStrength * val;
}

void AShip::ThrustYawActivate(float val)
{
	NoseYawThrust->Activate(true);
	TailYawThrust->Activate(true);
	NoseYawThrust->ThrustStrength = ThrustYawStrength * val;
	TailYawThrust->ThrustStrength = ThrustYawStrength * val;
	
}

void AShip::ThrustPitchActivate(float val)
{
	NosePitchThrust->Activate(true);
	TailPitchThrust->Activate(true);
	NosePitchThrust->ThrustStrength = ThrustPitchStrength * val;
	TailPitchThrust->ThrustStrength = ThrustPitchStrength * val;
}

void AShip::SetupThrusters()
{
	TArray<UActorComponent*> Thrusters;
	//	Thrusters = 
	Thrusters = this->GetComponentsByTag(UActorComponent::StaticClass(), FName("Thruster"));
	for (auto &thr : Thrusters) {
		FString NameThruster = thr->GetName();
		if (NameThruster.Contains(TEXT("RightWingRollThrust"))) { RightWingRollThrust = Cast<UPhysicsThrusterComponent>(thr); }
		if (NameThruster.Contains(TEXT("LeftWingRollThrust"))) { LeftWingRollThrust = Cast<UPhysicsThrusterComponent>(thr); }
		if (NameThruster.Contains(TEXT("NosePitchThrust"))) { NosePitchThrust = Cast<UPhysicsThrusterComponent>(thr); }
		if (NameThruster.Contains(TEXT("NoseYawThrust"))) { NoseYawThrust = Cast<UPhysicsThrusterComponent>(thr); }
		if (NameThruster.Contains(TEXT("TailPitchThrust"))) { TailPitchThrust = Cast<UPhysicsThrusterComponent>(thr); }
		if (NameThruster.Contains(TEXT("TailYawThrust"))) { TailYawThrust = Cast<UPhysicsThrusterComponent>(thr); }
		//LeftThruster->ThrustStrength = 15;
		//LeftThruster->ThrustStrength = 10000;
		UE_LOG(LogTemp, Warning, TEXT("Find Thrastor %s"), *thr->GetName());
	}
	if (!RightWingRollThrust) { UE_LOG(LogTemp, Error, TEXT("ERROR! NO FIND AND SETUP SHIP THRUSTER NAME: RightWingRollThrust"));}
	if (!LeftWingRollThrust) { UE_LOG(LogTemp, Error, TEXT("ERROR! NO FIND AND SETUP SHIP THRUSTER NAME: LeftWingRollThrust")); }
	if (!NosePitchThrust) { UE_LOG(LogTemp, Error, TEXT("ERROR! NO FIND AND SETUP SHIP THRUSTER NAME: NosePitchThrust")); }
	if (!NoseYawThrust) { UE_LOG(LogTemp, Error, TEXT("ERROR! NO FIND AND SETUP SHIP THRUSTER NAME: NoseYawThrust")); }
	if (!TailPitchThrust) { UE_LOG(LogTemp, Error, TEXT("ERROR! NO FIND AND SETUP SHIP THRUSTER NAME: TailPitchThrust")); }
	if (!TailYawThrust) { UE_LOG(LogTemp, Error, TEXT("ERROR! NO FIND AND SETUP SHIP THRUSTER NAME: TailYawThrust")); }

}

void AShip::Fly()
{

}

