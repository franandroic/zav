// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Map.h"
#include "Floor.h"
#include "MapGenerator.h"
#include "CubicleBox.h"
#include "CubicleSparky.h"
#include "SparkyPlayerController.h"
#include "GameFramework/GameModeBase.h"
#include "SparkyPuzzleGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SPARKYPUZZLE_API ASparkyPuzzleGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	ASparkyPuzzleGameModeBase();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void regenerateMap();

	void resetMap();

	int generateCubicles(MapGenerator map);

	MapGenerator generateMap(int x, int y, int l, int o);

private:

	ASparkyPlayerController *controller;

	UPROPERTY(EditAnywhere)
	int width = 10;

	UPROPERTY(EditAnywhere)
	int height = 10;

	UPROPERTY(EditAnywhere)
	int lines = 10;

	UPROPERTY(EditAnywhere)
	int objects = 20;

	UPROPERTY(VisibleAnywhere)
	FVector mapCenter;

	UPROPERTY(VisibleAnywhere)
	float longestSide;

	UPROPERTY(VisibleAnywhere)
	int seed;

	UPROPERTY(VisibleAnywhere)
	FVector2D endLocation;

	int newWidth;

	int newHeight;

	int newLines;

	void EndGame(bool bVictory);

	void DeleteMap();

public:

	ACubicle* SparkyHimself;

	FVector GetMapCenter();

	float GetLongestSide();

	int GetSeed();

	int GetWidth();

	int GetHeight();

	int GetLines();

	int GetNewWidth();

	int GetNewHeight();

	int GetNewLines();

	void AlterNewWidth(int diff);

	void AlterNewHeight(int diff);

	void AlterNewLines(int diff);

	TMap<FString, bool> GameMap;

	UPROPERTY(VisibleAnywhere)
	int state; //0 = IN_PROGRESS, 1 = SUCCESS, 2 = FAIL, 3 = IN_MOTION

	void ReloadMap();

	void RefreshMap();
	
};
