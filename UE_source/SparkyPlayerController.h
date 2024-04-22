// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BirdCamera.h"
#include "SparkyPlayerController.generated.h"


UCLASS()
class SPARKYPUZZLE_API ASparkyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;
	
};
