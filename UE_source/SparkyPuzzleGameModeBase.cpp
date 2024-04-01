// Copyright Epic Games, Inc. All Rights Reserved.


#include "SparkyPuzzleGameModeBase.h"
#include "Floor.h"
#include "MapGenerator.h"

void ASparkyPuzzleGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    srand(time(0));
    UE_LOG(LogTemp, Warning, TEXT("Seed: %d"), time(0));

    MapGenerator map(width, height, lines, objects);

    while (map.generatePaths()) {
        UE_LOG(LogTemp, Warning, TEXT("Regenerating..."));
    }

    map.placeBoxes();
    map.formatLayout();
    //map.printLog();

    FVector SpawnLocation = FVector(0.0f, 0.0f, 0.0f);
    AFloor *FloorTile = GetWorld()->SpawnActor<AFloor>(SpawnLocation, FRotator::ZeroRotator);
    if (FloorTile) FloorTile->SetActorScale3D(FVector(width, height, 1.0));

}
