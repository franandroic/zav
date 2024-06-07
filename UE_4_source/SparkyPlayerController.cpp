// Fill out your copyright notice in the Description page of Project Settings.


#include "SparkyPlayerController.h"
#include "SparkyPuzzleGameModeBase.h"

ASparkyPlayerController::ASparkyPlayerController()
{
    InputComponent = CreateDefaultSubobject<UInputComponent>(TEXT("InputComponent"));
    if (!InputComponent) {
        UE_LOG(LogTemp, Warning, TEXT("InputComponent failed."));
    }
    else {

        InputComponent->BindAction("Reload", IE_Pressed, this, &ASparkyPlayerController::ReloadMap);
        InputComponent->BindAction("Refresh", IE_Pressed, this, &ASparkyPlayerController::RefreshMap);
        InputComponent->BindAction("Select", IE_Pressed, this, &ASparkyPlayerController::SelectObject);
        InputComponent->BindAction("MoveUp", IE_Pressed, this, &ASparkyPlayerController::SlideUp);
        InputComponent->BindAction("MoveLeft", IE_Pressed, this, &ASparkyPlayerController::SlideLeft);
        InputComponent->BindAction("MoveDown", IE_Pressed, this, &ASparkyPlayerController::SlideDown);
        InputComponent->BindAction("MoveRight", IE_Pressed, this, &ASparkyPlayerController::SlideRight);
        InputComponent->BindAction("SwitchCamera", IE_Pressed, this, &ASparkyPlayerController::ChangeCamera);

        InputComponent->BindAction("GetInfo", IE_Pressed, this, &ASparkyPlayerController::ShowInfo);
        InputComponent->BindAction("WidthPlus", IE_Pressed, this, &ASparkyPlayerController::AddWidth);
        InputComponent->BindAction("WidthMinus", IE_Pressed, this, &ASparkyPlayerController::SubtractWidth);
        InputComponent->BindAction("HeightPlus", IE_Pressed, this, &ASparkyPlayerController::AddHeight);
        InputComponent->BindAction("HeightMinus", IE_Pressed, this, &ASparkyPlayerController::SubtractHeight);

    }
}


void ASparkyPlayerController::BeginPlay()
{
    Super::BeginPlay();

    bShowMouseCursor = true;

    UE_LOG(LogTemp, Warning, TEXT("BEGIN"));

    SelectedCubicle = nullptr;
}

void ASparkyPlayerController::SelectObject()
{   
    if (!GetWorld()) return;

    FVector2D screenPosition;
    FVector2D mousePosition;
    int windowSizeX;
    int windowSizeY;

    GetMousePosition(mousePosition.X, mousePosition.Y);
    GetViewportSize(windowSizeX, windowSizeY);

    for (TActorIterator<APawn> PawnItr(GetWorld()); PawnItr; ++PawnItr) {
        if (PawnItr->GetName().Left(7) == TEXT("Cubicle")) {

            if (UGameplayStatics::ProjectWorldToScreen(this, PawnItr->GetActorLocation(), screenPosition)) {
                if ((mousePosition - screenPosition).Size() < 25) {

                    ACubicle *ClickedCubicle = Cast<ACubicle>(*PawnItr);
                    if (!ClickedCubicle) return;
                    UE_LOG(LogTemp, Warning, TEXT("%s (%f, %f)"), *ClickedCubicle->GetName(), screenPosition.X, screenPosition.Y);

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
    }
}

void ASparkyPlayerController::SlideUp()
{
    if (!GetWorld()) return;
    ASparkyPuzzleGameModeBase* gamemode = Cast<ASparkyPuzzleGameModeBase>(GetWorld()->GetAuthGameMode());
    if (gamemode->state != 0) return;

    if (SelectedCubicle) {

        FString tempString;
        int currentX = SelectedCubicle->currentLocation.X;
        int currentY = SelectedCubicle->currentLocation.Y;

        gamemode->state = 3;

        for (int x = currentX + 1; x < gamemode->GetWidth(); x++) {

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

        SelectedCubicle->SlideMove(FVector((gamemode->GetWidth() + 5) * 300.0f, currentY * 300.0f, 121.1f));

        tempString = FString::FromInt(currentX) + "//" + FString::FromInt(currentY);
        gamemode->GameMap[tempString] = false;
        gamemode->state = 0;
    }
}

void ASparkyPlayerController::SlideLeft()
{
    if (!GetWorld()) return;
    ASparkyPuzzleGameModeBase* gamemode = Cast<ASparkyPuzzleGameModeBase>(GetWorld()->GetAuthGameMode());
    if (gamemode->state != 0) return;

    if (SelectedCubicle) {

        FString tempString;
        int currentX = SelectedCubicle->currentLocation.X;
        int currentY = SelectedCubicle->currentLocation.Y;

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
    if (!GetWorld()) return;
    ASparkyPuzzleGameModeBase* gamemode = Cast<ASparkyPuzzleGameModeBase>(GetWorld()->GetAuthGameMode());
    if (gamemode->state != 0) return;

    if (SelectedCubicle) {

        FString tempString;
        int currentX = SelectedCubicle->currentLocation.X;
        int currentY = SelectedCubicle->currentLocation.Y;

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
    if (!GetWorld()) return;
    ASparkyPuzzleGameModeBase* gamemode = Cast<ASparkyPuzzleGameModeBase>(GetWorld()->GetAuthGameMode());
    if (gamemode->state != 0) return;

    if (SelectedCubicle) {

        FString tempString;
        int currentX = SelectedCubicle->currentLocation.X;
        int currentY = SelectedCubicle->currentLocation.Y;

        gamemode->state = 3;

        for (int y = currentY + 1; y < gamemode->GetHeight(); y++) {

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

        SelectedCubicle->SlideMove(FVector(currentX * 300.0f, (gamemode->GetHeight() + 5) * 300.0f, 121.1f));

        tempString = FString::FromInt(currentX) + "//" + FString::FromInt(currentY);
        gamemode->GameMap[tempString] = false;
        gamemode->state = 0;
    }
}

void ASparkyPlayerController::ReloadMap()
{
    if (!GetWorld()) return;
    ASparkyPuzzleGameModeBase* gamemode = Cast<ASparkyPuzzleGameModeBase>(GetWorld()->GetAuthGameMode());

    gamemode->ReloadMap();
}

void ASparkyPlayerController::RefreshMap()
{
    if (!GetWorld()) return;
    ASparkyPuzzleGameModeBase* gamemode = Cast<ASparkyPuzzleGameModeBase>(GetWorld()->GetAuthGameMode());

    gamemode->RefreshMap();
}

void ASparkyPlayerController::ChangeCamera()
{
    if (!GetWorld()) return;

    if (GetViewTarget() == BirdCameraActorOne) SetViewTarget(BirdCameraActorTwo);
    else if (GetViewTarget() == BirdCameraActorTwo) SetViewTarget(BirdCameraActorOne);

}

void ASparkyPlayerController::ShowInfo()
{
    if (!GetWorld()) return;
    ASparkyPuzzleGameModeBase* gamemode = Cast<ASparkyPuzzleGameModeBase>(GetWorld()->GetAuthGameMode());

    float difficulty = (gamemode->GetLines() / 10) / ((gamemode->GetWidth() / 10) * (gamemode->GetHeight() / 10));

    if (GEngine) {
        GEngine->AddOnScreenDebugMessage(0, 10.0f, FColor::Black, FString::Printf(
            TEXT("<Top-To-Bottom: %d>\n<Left-To-Right: %d>\n<Count-Of-Lines: %d>\n<Difficulty: %.1f>"),
            gamemode->GetWidth(),
            gamemode->GetHeight(),
            gamemode->GetLines(),
            difficulty
        ));
    }
}

void ASparkyPlayerController::AddWidth()
{
    if (!GetWorld()) return;
    ASparkyPuzzleGameModeBase* gamemode = Cast<ASparkyPuzzleGameModeBase>(GetWorld()->GetAuthGameMode());

    if (gamemode->GetWidth() == 20 || gamemode->GetNewWidth() == 20) return;

    gamemode->AlterNewWidth(1);
}

void ASparkyPlayerController::SubtractWidth()
{
    if (!GetWorld()) return;
    ASparkyPuzzleGameModeBase* gamemode = Cast<ASparkyPuzzleGameModeBase>(GetWorld()->GetAuthGameMode());

    if (gamemode->GetWidth() == 10 || gamemode->GetNewWidth() == 10) return;

    gamemode->AlterNewWidth(-1);
}

void ASparkyPlayerController::AddHeight()
{
    if (!GetWorld()) return;
    ASparkyPuzzleGameModeBase* gamemode = Cast<ASparkyPuzzleGameModeBase>(GetWorld()->GetAuthGameMode());

    if (gamemode->GetHeight() == 20 || gamemode->GetNewHeight() == 20) return;

    gamemode->AlterNewHeight(1);
}

void ASparkyPlayerController::SubtractHeight()
{
    if (!GetWorld()) return;
    ASparkyPuzzleGameModeBase* gamemode = Cast<ASparkyPuzzleGameModeBase>(GetWorld()->GetAuthGameMode());

    if (gamemode->GetHeight() == 10 || gamemode->GetNewHeight() == 10) return;

    gamemode->AlterNewHeight(-1);
}

void ASparkyPlayerController::setupCameras()
{
    if (!GetWorld()) return;
    ASparkyPuzzleGameModeBase* gamemode = Cast<ASparkyPuzzleGameModeBase>(GetWorld()->GetAuthGameMode());

    FVector mapCenter = gamemode->GetMapCenter();
    float longestSide = gamemode->GetLongestSide();

    BirdCameraActorOne = GetWorld()->SpawnActor<ABirdCamera>(FVector(mapCenter.X, mapCenter.Y, longestSide + 900.0f), FRotator(-90.0f, 0.0f, 0.0f));
    BirdCameraActorTwo = GetWorld()->SpawnActor<ABirdCamera>(FVector(-900.0f - 0.2 * longestSide, mapCenter.Y, longestSide), FRotator(-1 * FMath::RadiansToDegrees(FMath::Atan(mapCenter.X / (longestSide + 900.0f))), 0.0f, 0.0f));

    SetViewTarget(BirdCameraActorOne);
}