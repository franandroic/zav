// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SparkyPlayer.generated.h"

UCLASS()
class SPARKYPUZZLE_API ASparkyPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASparkyPlayer();

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

	UPROPERTY(VisibleAnywhere)
	FVector2D currentLocation;

private:

	UStaticMeshComponent *MeshComponent;

};
