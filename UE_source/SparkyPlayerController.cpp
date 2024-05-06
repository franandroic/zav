// Fill out your copyright notice in the Description page of Project Settings.

#include "SparkyPuzzleGameModeBase.h"
#include "SparkyPlayerController.h"


ASparkyPlayerController::ASparkyPlayerController()
{
    InputComponent = CreateDefaultSubobject<UInputComponent>(TEXT("InputComponent"));
    if (!InputComponent) {
        UE_LOG(LogTemp, Warning, TEXT("InputComponent failed."));
    } else {
        InputComponent->BindAction("Reload", IE_Pressed, this, &ASparkyPlayerController::ReloadMap);
        InputComponent->BindAction("Select", IE_Pressed, this, &ASparkyPlayerController::SelectObject);
    }
}


void ASparkyPlayerController::BeginPlay()
{
    Super::BeginPlay();

    bShowMouseCursor = true;

    UE_LOG(LogTemp, Warning, TEXT("BEGIN"));

    ASparkyPuzzleGameModeBase *gamemode = Cast<ASparkyPuzzleGameModeBase>(GetWorld()->GetAuthGameMode());

    FVector mapCenter = gamemode->GetMapCenter();
    float longestSide = gamemode->GetLongestSide();

    ABirdCamera *BirdCameraActor = GetWorld()->SpawnActor<ABirdCamera>(FVector(mapCenter.X, mapCenter.Y, 2 * longestSide), FRotator(-90.0f, 0.0f, 0.0f));

    SetViewTarget(BirdCameraActor);


    SelectedSparky = nullptr;
    SelectedCubicle = nullptr;
}


void ASparkyPlayerController::ReloadMap()
{
    ASparkyPuzzleGameModeBase *gamemode = Cast<ASparkyPuzzleGameModeBase>(GetWorld()->GetAuthGameMode());

    for (TActorIterator<APawn> PawnItr(GetWorld()); PawnItr; ++PawnItr) {
        if (PawnItr->GetName().Left(7) == TEXT("Cubicle") || PawnItr->GetName().Left(12) == TEXT("SparkyPlayer")) PawnItr->Destroy();
    }

    for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
        if (ActorItr->GetName().Left(5) == TEXT("Floor")) ActorItr->Destroy();
    }


    gamemode->regenerateMap();
}

void ASparkyPlayerController::SelectObject()
{
    TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
    FHitResult HitResult;

    ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));

    if (GetHitResultUnderCursorForObjects(ObjectTypes, false, HitResult)) {

        ACubicle *ClickedCubicle = Cast<ACubicle>(HitResult.GetActor());
        if (ClickedCubicle) {

            UE_LOG(LogTemp, Warning, TEXT("Clicked on cubicle: %s."), *ClickedCubicle->GetName());

            if (SelectedSparky) {
                SelectedSparky->bIsSelected = false;
                SelectedSparky = nullptr;
            } else if (SelectedCubicle) {
                SelectedCubicle->bIsSelected = false;
            }

            ClickedCubicle->bIsSelected = true;
            SelectedCubicle = ClickedCubicle;
        }

        ASparkyPlayer *ClickedSparky = Cast<ASparkyPlayer>(HitResult.GetActor());
        if (ClickedSparky) {

            UE_LOG(LogTemp, Warning, TEXT("Clicked on Sparky himself: %s."), *ClickedSparky->GetName());

            if (!SelectedSparky) {
                SelectedCubicle->bIsSelected = false;
                SelectedCubicle = nullptr;
                ClickedSparky->bIsSelected = true;
                SelectedSparky = ClickedSparky;
            }
        }

    }
}