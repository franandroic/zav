// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerController.h"
#include "Cubicle.h"
#include "BirdCamera.h"
#include "Kismet/GameplayStatics.h"
#include "SparkyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SPARKYPUZZLE_API ASparkyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	ASparkyPlayerController();

	virtual void BeginPlay() override;

	void SelectObject();

	void SlideUp();

	void SlideLeft();

	void SlideDown();

	void SlideRight();

private:

	ABirdCamera* BirdCameraActor;

	ACubicle* SelectedCubicle;

	void ReloadMap();

	void RefreshMap();
	
};
