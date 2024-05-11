// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Map.h"
#include "Floor.h"
#include "MapGenerator.h"
#include "Cubicle.h"
#include "SparkyPlayer.h"
#include "SparkyPlayerController.h"
#include "GameFramework/GameModeBase.h"
#include "SparkyPuzzleGameModeBase.generated.h"


UCLASS()
class SPARKYPUZZLE_API ASparkyPuzzleGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	ASparkyPuzzleGameModeBase();

	virtual void BeginPlay() override;

	void regenerateMap();

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

	UPROPERTY(EditAnywhere)
	FVector mapCenter;

	UPROPERTY(EditAnywhere)
	float longestSide;

public:

	FVector GetMapCenter();

	float GetLongestSide();

	int GetWidth();

	int GetHeight();

	TMap<FString, bool> GameMap;
	
};
