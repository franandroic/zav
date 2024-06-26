// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Cubicle.generated.h"

UCLASS()
class SPARKYPUZZLE_API ACubicle : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACubicle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
	bool bIsSelected;

	void ToggleMaterial();

	void SlideMove(FVector EndLocation);

	UPROPERTY(VisibleAnywhere)
	FVector2D currentLocation;

	UPROPERTY(VisibleAnywhere)
	bool bIsSparky;

	UPROPERTY(VisibleAnywhere)
	bool bIsMoving;

protected:

	UStaticMeshComponent* MeshComponent;

	UMaterialInterface* CubicleMaterial;
	UMaterialInterface* CubicleHMaterial;

	FVector MoveEndLocation;

	FVector MoveDirection;

};
