// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SparkyPuzzleGameModeBase.generated.h"


UCLASS()
class SPARKYPUZZLE_API ASparkyPuzzleGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	int width = 10;

	UPROPERTY(EditAnywhere)
	int height = 10;

	UPROPERTY(EditAnywhere)
	int lines = 10;

	UPROPERTY(EditAnywhere)
	int objects = 20;
	
};
