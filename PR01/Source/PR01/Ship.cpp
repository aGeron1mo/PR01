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
	InputComp = GetWorld()->GetFirstPlayerController()->GetPawn()->FindComponentByClass<UInputComponent>();

	if (InputComp) {
		InputComp->BindAction(FName(TEXT("Accelerator")), EInputEvent::IE_Repeat, this, &AShip::SpeedUp);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Input component not found"));
	}
	
//	AActor* Act = GetWorld()->GetFirstPlayerController->GetPawn();

//	UE_LOG(LogTemp, Warning, TEXT("Actor name: %s"), *GetOwner()->GetName());

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

void AShip::SpeedUp()
{
	ShipSpeedUp += 1.f;

	UE_LOG(LogTemp, Warning, TEXT("Speed Up %f"), ShipSpeedUp);

}

void AShip::Fly()
{
	AActor* Act = GetWorld()->GetFirstPlayerController()->GetPawn();
	ShipLocation += FVector(ShipSpeedUp, 0, 0);
	Act->SetActorLocation(ShipLocation);
}

