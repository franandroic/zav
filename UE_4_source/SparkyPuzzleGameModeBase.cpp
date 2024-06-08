// Copyright Epic Games, Inc. All Rights Reserved.


#include "SparkyPuzzleGameModeBase.h"

ASparkyPuzzleGameModeBase::ASparkyPuzzleGameModeBase()
{
    PrimaryActorTick.bCanEverTick = true;
    PlayerControllerClass = ASparkyPlayerController::StaticClass();
    DefaultPawnClass = nullptr;
}

void ASparkyPuzzleGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    newWidth = width;
    newHeight = height;
    newLines = lines;

    controller = Cast<ASparkyPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    regenerateMap();
}

void ASparkyPuzzleGameModeBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (state == 0) {
        if (SparkyHimself->currentLocation.X == endLocation.X && SparkyHimself->currentLocation.Y == endLocation.Y && SparkyHimself->bIsMoving == false) {
            EndGame(true);
        }
        else if (SparkyHimself->currentLocation.X < 0 || SparkyHimself->currentLocation.X > width || SparkyHimself->currentLocation.Y < 0 || SparkyHimself->currentLocation.Y > height) {
            EndGame(false);
        }
    }
}

void ASparkyPuzzleGameModeBase::regenerateMap()
{
    seed = time(0);

    width = newWidth;
    height = newHeight;
    lines = newLines;

    resetMap();
    if (controller) controller->setupCameras();
}

void ASparkyPuzzleGameModeBase::resetMap()
{
    srand(seed);

    MapGenerator map = generateMap(width, height, lines, objects);

    generateCubicles(map);

    state = 0;
}

int ASparkyPuzzleGameModeBase::generateCubicles(MapGenerator map)
{
    AFloor* FloorTile = GetWorld()->SpawnActor<AFloor>(FVector(0.0f, 0.0f, 0.0f), FRotator::ZeroRotator);
    if (!FloorTile) return 1;

    FVector FloorOrigin;
    FVector FloorExtent;

    FloorTile->GetActorBounds(false, FloorOrigin, FloorExtent);
    float floorTileX = (FloorExtent.X * 2.0f);
    float floorTileY = (FloorExtent.Y * 2.0f);
    float floorTileZ = (FloorExtent.Z * 2.0f);

    FloorTile->SetActorScale3D(FVector(width, height, 1.0));
    FloorTile->AddActorLocalOffset(FVector(((floorTileX * width) / 2) - FloorExtent.X, ((floorTileY * height) / 2) - FloorExtent.Y, 0.0f));

    GameMap.Empty();
    FString tempString;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {

            if (map.MAP_MATRIX[y][x] == 'B') {

                ACubicle* BoxCubicle = GetWorld()->SpawnActor<ACubicleBox>(FVector(x * floorTileX, y * floorTileY, 121.0f), FRotator::ZeroRotator);

                if (BoxCubicle) {
                    BoxCubicle->currentLocation = FVector2D(x, y);
                    tempString = FString::FromInt(x) + "//" + FString::FromInt(y);
                    GameMap.Add(tempString, true);
                }
                else return 1;

            }
            else if (map.MAP_MATRIX[y][x] == 'S') {

                ACubicle* SparkyCubicle = GetWorld()->SpawnActor<ACubicleSparky>(FVector(x * floorTileX, y * floorTileY, 121.0f), FRotator::ZeroRotator);

                if (SparkyCubicle) {
                    SparkyCubicle->currentLocation = FVector2D(x, y);
                    tempString = FString::FromInt(x) + "//" + FString::FromInt(y);
                    GameMap.Add(tempString, true);
                    SparkyHimself = SparkyCubicle;
                }
                else return 1;

            }
            else if (map.MAP_MATRIX[y][x] == 'X') {
                AFloor* EndTile = GetWorld()->SpawnActor<AFloor>(FVector(x * floorTileX, y * floorTileY, 25.0f), FRotator::ZeroRotator);
                if (EndTile) {
                    EndTile->SetActorScale3D(FVector(1.0, 1.0, 0.25));
                    EndTile->ApplyEndpointMaterial();
                    endLocation = FVector2D(x, y);
                }
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

int ASparkyPuzzleGameModeBase::GetSeed()
{
    return seed;
}

int ASparkyPuzzleGameModeBase::GetWidth()
{
    return width;
}

int ASparkyPuzzleGameModeBase::GetHeight()
{
    return height;
}

int ASparkyPuzzleGameModeBase::GetLines()
{
    return lines;
}

int ASparkyPuzzleGameModeBase::GetNewWidth()
{
    return newWidth;
}

int ASparkyPuzzleGameModeBase::GetNewHeight()
{
    return newHeight;
}

int ASparkyPuzzleGameModeBase::GetNewLines()
{
    return newLines;
}

void ASparkyPuzzleGameModeBase::AlterNewWidth(int diff)
{
    newWidth += diff;
}

void ASparkyPuzzleGameModeBase::AlterNewHeight(int diff)
{
    newHeight += diff;
}

void ASparkyPuzzleGameModeBase::AlterNewLines(int diff)
{
    newLines += diff;
}

void ASparkyPuzzleGameModeBase::EndGame(bool bVictory)
{
    if (bVictory) {
        state = 1;
        UE_LOG(LogTemp, Warning, TEXT("Victory!"));
        ReloadMap();
        state = 0;
    }
    else {
        state = 2;
        UE_LOG(LogTemp, Warning, TEXT("Defeat!"));
        RefreshMap();
        state = 0;
    }
}

void ASparkyPuzzleGameModeBase::ReloadMap()
{
    DeleteMap();

    regenerateMap();
}

void ASparkyPuzzleGameModeBase::RefreshMap()
{
    DeleteMap();

    resetMap();
}

void ASparkyPuzzleGameModeBase::DeleteMap()
{
    for (TActorIterator<APawn> PawnItr(GetWorld()); PawnItr; ++PawnItr) {
        if (PawnItr->GetName().Left(7) == TEXT("Cubicle")) PawnItr->Destroy();
    }

    for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
        if (ActorItr->GetName().Left(5) == TEXT("Floor")) ActorItr->Destroy();
    }

    controller->dereferenceSelected();
}
