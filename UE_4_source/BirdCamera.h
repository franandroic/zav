// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "BirdCamera.generated.h"

UCLASS()
class SPARKYPUZZLE_API ABirdCamera : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ABirdCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

public:

	UCameraComponent* GetCameraComponent();

};
