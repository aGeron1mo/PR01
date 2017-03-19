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

	SetupEngines();
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
	if (val) {
		RightWingRollThrust->Activate(true);
		LeftWingRollThrust->Activate(true);
		RightWingRollThrust->ThrustStrength = ThrustRollStrength * val;
		LeftWingRollThrust->ThrustStrength = ThrustRollStrength * val;
	}
	else {
		RightWingRollThrust->Deactivate();
		LeftWingRollThrust->Deactivate();
	}
}

void AShip::ThrustYawActivate(float val)
{
	if (val) {
		NoseYawThrust->Activate(true);
		TailYawThrust->Activate(true);
		NoseYawThrust->ThrustStrength = ThrustYawStrength * val;
		TailYawThrust->ThrustStrength = ThrustYawStrength * val;
	}
	else {
		NoseYawThrust->Deactivate();
		TailYawThrust->Deactivate();
	}
}

void AShip::ThrustPitchActivate(float val)
{
	if (val) {
		NosePitchThrust->Activate(true);
		TailPitchThrust->Activate(true);
		NosePitchThrust->ThrustStrength = ThrustPitchStrength * val;
		TailPitchThrust->ThrustStrength = ThrustPitchStrength * val;
	}
	else {
		NosePitchThrust->Deactivate();
		TailPitchThrust->Deactivate();
	}
}

void AShip::ThrustEngineActivate(float val)
{
//	ShipMainSM->AddImpulse(RootDirectionArrow->GetForwardVector() * EnginePower * val);
	current_engine_val += val;
	current_engine_val = FMath::Clamp<float>(current_engine_val, 0, 100); // 0 - 100 % Power
	if (current_engine_val) {
		ShipMainSM->AddImpulse(RootDirectionArrow->GetForwardVector() * EnginePower * current_engine_val / 100);
		//ShipMainSM->SetPhysicsLinearVelocity(RootDirectionArrow->GetForwardVector() * EnginePower * current_engine_val / 100);
	}
}

void AShip::FirePrimary(float val)
{
	bool isReloaded = (FPlatformTime::Seconds() - ProjectileLastFireTime) > ProjectileTimeReloadInSec;
	if (val && isReloaded) {
		UE_LOG(LogTemp, Warning, TEXT("The fire of the main gun !"));
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(Projectile_BluePrint, RootDirectionArrow->GetComponentLocation() + RootDirectionArrow->GetComponentRotation().Vector() * 100, RootDirectionArrow->GetComponentRotation());
		Projectile->SetLifeSpan(2);
		Projectile->StartProjectile(4000);
		ProjectileLastFireTime = FPlatformTime::Seconds();
	}
}

void AShip::Boost()
{
	ShipMainSM->AddImpulse(RootDirectionArrow->GetForwardVector() * BoostPower);
	UE_LOG(LogTemp, Warning, TEXT("Burst !"));
	OnBoost.Broadcast();

}

void AShip::SetupEngines()
{
	//	Find Thruster Engine And Setup
	TArray<UActorComponent*> Thrusters;
	Thrusters = this->GetComponentsByTag(UActorComponent::StaticClass(), FName("Thruster"));
	for (auto &thr : Thrusters) {
		FString NameThruster = thr->GetName();
		if (NameThruster.Contains(TEXT("RightWingRollThrust"))) { RightWingRollThrust = Cast<UPhysicsThrusterComponent>(thr); }
		if (NameThruster.Contains(TEXT("LeftWingRollThrust"))) { LeftWingRollThrust = Cast<UPhysicsThrusterComponent>(thr); }
		if (NameThruster.Contains(TEXT("NosePitchThrust"))) { NosePitchThrust = Cast<UPhysicsThrusterComponent>(thr); }
		if (NameThruster.Contains(TEXT("NoseYawThrust"))) { NoseYawThrust = Cast<UPhysicsThrusterComponent>(thr); }
		if (NameThruster.Contains(TEXT("TailPitchThrust"))) { TailPitchThrust = Cast<UPhysicsThrusterComponent>(thr); }
		if (NameThruster.Contains(TEXT("TailYawThrust"))) { TailYawThrust = Cast<UPhysicsThrusterComponent>(thr); }
//		if (NameThruster.Contains(TEXT("MainEngine"))) { MainEngine = Cast<UPhysicsThrusterComponent>(thr); }
			//MainEngine
	}
	if (!RightWingRollThrust) { UE_LOG(LogTemp, Error, TEXT("ERROR! NO FIND AND SETUP SHIP THRUSTER NAME: RightWingRollThrust"));}
	if (!LeftWingRollThrust) { UE_LOG(LogTemp, Error, TEXT("ERROR! NO FIND AND SETUP SHIP THRUSTER NAME: LeftWingRollThrust")); }
	if (!NosePitchThrust) { UE_LOG(LogTemp, Error, TEXT("ERROR! NO FIND AND SETUP SHIP THRUSTER NAME: NosePitchThrust")); }
	if (!NoseYawThrust) { UE_LOG(LogTemp, Error, TEXT("ERROR! NO FIND AND SETUP SHIP THRUSTER NAME: NoseYawThrust")); }
	if (!TailPitchThrust) { UE_LOG(LogTemp, Error, TEXT("ERROR! NO FIND AND SETUP SHIP THRUSTER NAME: TailPitchThrust")); }
	if (!TailYawThrust) { UE_LOG(LogTemp, Error, TEXT("ERROR! NO FIND AND SETUP SHIP THRUSTER NAME: TailYawThrust")); }
//	if (!MainEngine) { UE_LOG(LogTemp, Error, TEXT("ERROR! NO FIND AND SETUP MAIN ENGINE: MainEngine")); }

	//	Find Arrow Root Direction
	TArray<UActorComponent*> Arrows;
	Arrows = this->GetComponentsByTag(UActorComponent::StaticClass(), FName("RootDirectionArrow"));
	for (auto &arw : Arrows) {
		FString NameArrowsr = arw->GetName();
		if (NameArrowsr.Contains(TEXT("RootDirectionArrow"))) { RootDirectionArrow = Cast<UArrowComponent>(arw); }
	}
	if (!RootDirectionArrow) { UE_LOG(LogTemp, Error, TEXT("ERROR! NO FIND AND SETUP SHIP ROOT DIRECTION ARROW NAME: RootDirectionArrow")); }

	// Find Main Static Mesh (MainSM)
	TArray<UActorComponent*> Mesh;
	Mesh = this->GetComponentsByTag(UActorComponent::StaticClass(), FName("MainSM"));
	for (auto &mes : Mesh) {
		FString NameMesh = mes->GetName();
		if (NameMesh.Contains(TEXT("Ship"))) { ShipMainSM = Cast<UStaticMeshComponent>(mes); }
	}
	if (!ShipMainSM) { UE_LOG(LogTemp, Error, TEXT("ERROR! NO FIND AND SETUP MAIN STATIC MESH COMPONENT: MainSM")); }

}

void AShip::Fly()
{

}

