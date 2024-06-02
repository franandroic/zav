// Fill out your copyright notice in the Description page of Project Settings.


#include "Cubicle.h"

// Sets default values
ACubicle::ACubicle()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACubicle::BeginPlay()
{
	Super::BeginPlay();
	
	bIsMoving = false;
}

// Called every frame
void ACubicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UE_LOG(LogTemp, Warning, TEXT("%d"), bIsMoving);

	if (bIsMoving) {

		FVector locationIncrement = GetActorLocation() + MoveDirection * 6000.0f * DeltaTime;
		SetActorLocation(locationIncrement);

		//UE_LOG(LogTemp, Warning, TEXT("A: %f %f %f, B: %f %f %f"), GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z, MoveEndLocation.X, MoveEndLocation.Y, MoveEndLocation.Z);

		if ((GetActorLocation() - MoveEndLocation).Size() < 100.0f) {
			bIsMoving = false;
			SetActorLocation(MoveEndLocation);
			if (MoveEndLocation.Z == 121.1f) Destroy();
		}

	}

}

// Called to bind functionality to input
void ACubicle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACubicle::ToggleMaterial()
{
		if (!bIsSelected) {
			if (CubicleMaterial) MeshComponent->SetMaterial(0, CubicleMaterial);
		} else {
			if (CubicleMaterial) MeshComponent->SetMaterial(0, CubicleHMaterial);
		}
}

void ACubicle::SlideMove(FVector EndLocation)
{
	if (!bIsMoving) {
		MoveEndLocation = EndLocation;
		MoveDirection = (MoveEndLocation - GetActorLocation()).GetSafeNormal();
		bIsMoving = true;
	}
}