// Fill out your copyright notice in the Description page of Project Settings.

#include "SparkyPlayerController.h"
#include "SparkyPuzzleGameModeBase.h"

ASparkyPlayerController::ASparkyPlayerController()
{
    InputComponent = CreateDefaultSubobject<UInputComponent>(TEXT("InputComponent"));
    if (!InputComponent) {
        UE_LOG(LogTemp, Warning, TEXT("InputComponent failed."));
    } else {
        InputComponent->BindAction("Reload", IE_Pressed, this, &ASparkyPlayerController::ReloadMap);
        InputComponent->BindAction("Refresh", IE_Pressed, this, &ASparkyPlayerController::RefreshMap);
        InputComponent->BindAction("Select", IE_Pressed, this, &ASparkyPlayerController::SelectObject);
        InputComponent->BindAction("MoveUp", IE_Pressed, this, &ASparkyPlayerController::SlideUp);
        InputComponent->BindAction("MoveLeft", IE_Pressed, this, &ASparkyPlayerController::SlideLeft);
        InputComponent->BindAction("MoveDown", IE_Pressed, this, &ASparkyPlayerController::SlideDown);
        InputComponent->BindAction("MoveRight", IE_Pressed, this, &ASparkyPlayerController::SlideRight);
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

    SelectedCubicle = nullptr;
}

void ASparkyPlayerController::SelectObject()
{
    TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
    FHitResult HitResult;

    ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));

    if (GetHitResultUnderCursorForObjects(ObjectTypes, false, HitResult)) {

        if (HitResult.GetActor()->IsA<ACubicle>()) {

            ACubicle *ClickedCubicle = Cast<ACubicle>(HitResult.GetActor());

            UE_LOG(LogTemp, Warning, TEXT("Clicked on cubicle: %s."), *ClickedCubicle->GetName());

            if (SelectedCubicle) {
                SelectedCubicle->bIsSelected = false;
                SelectedCubicle->ToggleMaterial();
            }

            ClickedCubicle->bIsSelected = true;
            ClickedCubicle->ToggleMaterial();
            SelectedCubicle = ClickedCubicle;

        }

    }
}

void ASparkyPlayerController::SlideUp()
{
    ASparkyPuzzleGameModeBase *gamemode = Cast<ASparkyPuzzleGameModeBase>(GetWorld()->GetAuthGameMode());
    if (gamemode->state != 0) return;

    FString tempString;
    int currentX = SelectedCubicle->currentLocation.X;
    int currentY = SelectedCubicle->currentLocation.Y;

    if (SelectedCubicle) {

        gamemode->state = 3;

        for (int x = currentX + 1; x < gamemode->GetHeight(); x++) {
            
            tempString = FString::FromInt(x) + "//" + FString::FromInt(currentY);

            if (gamemode->GameMap.Contains(tempString) && gamemode->GameMap[tempString] == true) {

                if (x == currentX + 1) {
                    gamemode->state = 0;
                    return;
                }

                SelectedCubicle->SlideMove(FVector((x - 1) * 300.0f, currentY * 300.0f, 121.0f));

                tempString = FString::FromInt(currentX) + "//" + FString::FromInt(currentY);
                gamemode->GameMap[tempString] = false;

                tempString = FString::FromInt(x - 1) + "//" + FString::FromInt(currentY);
                if (gamemode->GameMap.Contains(tempString)) gamemode->GameMap[tempString] = true;
                else gamemode->GameMap.Add(tempString, true);

                SelectedCubicle->currentLocation.X = x - 1;

                gamemode->state = 0;

                return;
            }
        }

        SelectedCubicle->SlideMove(FVector((gamemode->GetHeight() + 5) * 300.0f, currentY * 300.0f, 121.1f));

        tempString = FString::FromInt(currentX) + "//" + FString::FromInt(currentY);
        gamemode->GameMap[tempString] = false;
        gamemode->state = 0;
    }
}

void ASparkyPlayerController::SlideLeft()
{
    ASparkyPuzzleGameModeBase *gamemode = Cast<ASparkyPuzzleGameModeBase>(GetWorld()->GetAuthGameMode());
    if (gamemode->state != 0) return;

    FString tempString;
    int currentX = SelectedCubicle->currentLocation.X;
    int currentY = SelectedCubicle->currentLocation.Y;

    if (SelectedCubicle) {

        gamemode->state = 3;

        for (int y = currentY - 1; y >= 0; y--) {
            
            tempString = FString::FromInt(currentX) + "//" + FString::FromInt(y);

            if (gamemode->GameMap.Contains(tempString) && gamemode->GameMap[tempString] == true) {

                if (y == currentY - 1) {
                    gamemode->state = 0;
                    return;
                }

                SelectedCubicle->SlideMove(FVector(currentX * 300.0f, (y + 1) * 300.0f, 121.0f));

                tempString = FString::FromInt(currentX) + "//" + FString::FromInt(currentY);
                gamemode->GameMap[tempString] = false;

                tempString = FString::FromInt(currentX) + "//" + FString::FromInt(y + 1);
                if (gamemode->GameMap.Contains(tempString)) gamemode->GameMap[tempString] = true;
                else gamemode->GameMap.Add(tempString, true);

                SelectedCubicle->currentLocation.Y = y + 1;

                gamemode->state = 0;

                return;
            }
        }

        SelectedCubicle->SlideMove(FVector(currentX * 300.0f, -5 * 300.0f, 121.1f));

        tempString = FString::FromInt(currentX) + "//" + FString::FromInt(currentY);
        gamemode->GameMap[tempString] = false;
        gamemode->state = 0;
    }
}

void ASparkyPlayerController::SlideDown()
{
    ASparkyPuzzleGameModeBase *gamemode = Cast<ASparkyPuzzleGameModeBase>(GetWorld()->GetAuthGameMode());
    if (gamemode->state != 0) return;

    FString tempString;
    int currentX = SelectedCubicle->currentLocation.X;
    int currentY = SelectedCubicle->currentLocation.Y;

    if (SelectedCubicle) {

        gamemode->state = 3;

        for (int x = currentX - 1; x >= 0; x--) {
            
            tempString = FString::FromInt(x) + "//" + FString::FromInt(currentY);

            if (gamemode->GameMap.Contains(tempString) && gamemode->GameMap[tempString] == true) {

                if (x == currentX - 1) {
                    gamemode->state = 0;
                    return;
                }

                SelectedCubicle->SlideMove(FVector((x + 1) * 300.0f, currentY * 300.0f, 121.0f));

                tempString = FString::FromInt(currentX) + "//" + FString::FromInt(currentY);
                gamemode->GameMap[tempString] = false;

                tempString = FString::FromInt(x + 1) + "//" + FString::FromInt(currentY);
                if (gamemode->GameMap.Contains(tempString)) gamemode->GameMap[tempString] = true;
                else gamemode->GameMap.Add(tempString, true);

                SelectedCubicle->currentLocation.X = x + 1;

                gamemode->state = 0;

                return;
            }
        }

        SelectedCubicle->SlideMove(FVector(-5 * 300.0f, currentY * 300.0f, 121.1f));

        tempString = FString::FromInt(currentX) + "//" + FString::FromInt(currentY);
        gamemode->GameMap[tempString] = false;
        gamemode->state = 0;
    }
}

void ASparkyPlayerController::SlideRight()
{
    ASparkyPuzzleGameModeBase *gamemode = Cast<ASparkyPuzzleGameModeBase>(GetWorld()->GetAuthGameMode());
    if (gamemode->state != 0) return;

    FString tempString;
    int currentX = SelectedCubicle->currentLocation.X;
    int currentY = SelectedCubicle->currentLocation.Y;

    if (SelectedCubicle) {

        gamemode->state = 3;

        for (int y = currentY + 1; y < gamemode->GetWidth(); y++) {
            
            tempString = FString::FromInt(currentX) + "//" + FString::FromInt(y);

            if (gamemode->GameMap.Contains(tempString) && gamemode->GameMap[tempString] == true) {

                if (y == currentY + 1) {
                    gamemode->state = 0;
                    return;
                }

                SelectedCubicle->SlideMove(FVector(currentX * 300.0f, (y - 1) * 300.0f, 121.0f));

                tempString = FString::FromInt(currentX) + "//" + FString::FromInt(currentY);
                gamemode->GameMap[tempString] = false;

                tempString = FString::FromInt(currentX) + "//" + FString::FromInt(y - 1);
                if (gamemode->GameMap.Contains(tempString)) gamemode->GameMap[tempString] = true;
                else gamemode->GameMap.Add(tempString, true);

                SelectedCubicle->currentLocation.Y = y - 1;

                gamemode->state = 0;

                return;
            }
        }

        SelectedCubicle->SlideMove(FVector(currentX * 300.0f, (gamemode->GetWidth() + 5) * 300.0f, 121.1f));

        tempString = FString::FromInt(currentX) + "//" + FString::FromInt(currentY);
        gamemode->GameMap[tempString] = false;
        gamemode->state = 0;
    }
}

void ASparkyPlayerController::ReloadMap()
{
    ASparkyPuzzleGameModeBase *gamemode = Cast<ASparkyPuzzleGameModeBase>(GetWorld()->GetAuthGameMode());

    gamemode->ReloadMap();
}

void ASparkyPlayerController::RefreshMap()
{
    ASparkyPuzzleGameModeBase *gamemode = Cast<ASparkyPuzzleGameModeBase>(GetWorld()->GetAuthGameMode());

    gamemode->RefreshMap();
}