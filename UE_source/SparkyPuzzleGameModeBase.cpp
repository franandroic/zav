// Copyright Epic Games, Inc. All Rights Reserved.


#include "SparkyPuzzleGameModeBase.h"

ASparkyPuzzleGameModeBase::ASparkyPuzzleGameModeBase()
{
    PlayerControllerClass = ASparkyPlayerController::StaticClass();
    DefaultPawnClass = nullptr;
}

void ASparkyPuzzleGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    srand(time(0));
    UE_LOG(LogTemp, Warning, TEXT("Seed: %d"), time(0));

    MapGenerator map = generateMap(width, height, lines, objects);

    generateCubicles(map);
}

int ASparkyPuzzleGameModeBase::generateCubicles(MapGenerator map)
{
    AFloor *FloorTile = GetWorld()->SpawnActor<AFloor>(FVector(0.0f, 0.0f, 0.0f), FRotator::ZeroRotator);
    if (!FloorTile) return 1;

    FVector FloorOrigin;
    FVector FloorExtent;

    FloorTile->GetActorBounds(false, FloorOrigin, FloorExtent);
    float floorTileX = (FloorExtent.X * 2.0f);
    float floorTileY = (FloorExtent.Y * 2.0f);
    float floorTileZ = (FloorExtent.Z * 2.0f);

    FloorTile->SetActorScale3D(FVector(width, height, 1.0));
    FloorTile->AddActorLocalOffset(FVector(((floorTileX * width) / 2) - FloorExtent.X, ((floorTileY * height) / 2) - FloorExtent.Y, 0.0f));

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (map.MAP_MATRIX[y][x] == 'B') {
                ACubicle *BoxCubicle = GetWorld()->SpawnActor<ACubicle>(FVector(x * floorTileX, y * floorTileY, 121.0f), FRotator::ZeroRotator);
                if (BoxCubicle) BoxCubicle->SetActorScale3D(FVector(1.0, 1.0, 1.0));
                else return 1;
            } else if (map.MAP_MATRIX[y][x] == 'S') {
                ASparkyPlayer *SparkyCubicle = GetWorld()->SpawnActor<ASparkyPlayer>(FVector(x * floorTileX, y * floorTileY, 121.0f), FRotator::ZeroRotator);
                if (SparkyCubicle) SparkyCubicle->SetActorScale3D(FVector(1.0, 1.0, 1.0));
                else return 1;
            } else if (map.MAP_MATRIX[y][x] == 'X') {
                AFloor *EndTile = GetWorld()->SpawnActor<AFloor>(FVector(x * floorTileX, y * floorTileY, 25.0f), FRotator::ZeroRotator);
                if (EndTile) EndTile->SetActorScale3D(FVector(1.0, 1.0, 0.25));
                else return 1;
            }
        }
    }

    FloorTile->GetActorBounds(false, FloorOrigin, FloorExtent);
    mapCenter = FloorOrigin;
    longestSide = FMath::Max(FloorExtent.X, FloorExtent.Y);

    return 0;
}

MapGenerator ASparkyPuzzleGameModeBase::generateMap(int x, int y, int l, int o)
{
    MapGenerator map(x, y, l, o);

    while (map.generatePaths()) {
        UE_LOG(LogTemp, Warning, TEXT("Regenerating..."));
    }

    map.placeBoxes();
    map.formatLayout();
    //map.printLog();

    return map;
}

FVector ASparkyPuzzleGameModeBase::GetMapCenter()
{
    return mapCenter;
}

float ASparkyPuzzleGameModeBase::GetLongestSide()
{
    return longestSide;
}