// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerController.h"
#include "SparkyPlayer.h"
#include "Cubicle.h"
#include "BirdCamera.h"
#include "SparkyPlayerController.generated.h"

UCLASS()
class SPARKYPUZZLE_API ASparkyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	ASparkyPlayerController();

	virtual void BeginPlay() override;

	void ReloadMap();

	void SelectObject();

private:

	UPROPERTY(VisibleAnywhere)
	ASparkyPlayer *SelectedSparky;

	UPROPERTY(VisibleAnywhere)
	ACubicle *SelectedCubicle;
	
};
