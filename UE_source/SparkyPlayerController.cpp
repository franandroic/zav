// Fill out your copyright notice in the Description page of Project Settings.

#include "SparkyPuzzleGameModeBase.h"
#include "SparkyPlayerController.h"

void ASparkyPlayerController::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Warning, TEXT("BEGIN"));

    ASparkyPuzzleGameModeBase *gamemode = Cast<ASparkyPuzzleGameModeBase>(GetWorld()->GetAuthGameMode());

    FVector mapCenter = gamemode->GetMapCenter();
    float longestSide = gamemode->GetLongestSide();

    ABirdCamera *BirdCameraActor = GetWorld()->SpawnActor<ABirdCamera>(FVector(mapCenter.X, mapCenter.Y, 2 * longestSide), FRotator(-90.0f, 0.0f, 0.0f));

    SetViewTarget(BirdCameraActor);

}