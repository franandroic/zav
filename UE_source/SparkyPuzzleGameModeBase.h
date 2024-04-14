// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Floor.h"
#include "MapGenerator.h"
#include "Cubicle.h"
#include "SparkyPlayer.h"
#include "GameFramework/GameModeBase.h"
#include "SparkyPuzzleGameModeBase.generated.h"


UCLASS()
class SPARKYPUZZLE_API ASparkyPuzzleGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	int generateCubicles(MapGenerator map);

	MapGenerator generateMap(int x, int y, int l, int o);

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
