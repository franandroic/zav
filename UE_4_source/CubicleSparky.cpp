// Fill out your copyright notice in the Description page of Project Settings.


#include "CubicleSparky.h"

ACubicleSparky::ACubicleSparky()
{
    bIsSparky = true;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/sparkyM.sparkyM'"));
    if (MeshAsset.Succeeded()) MeshComponent->SetStaticMesh(MeshAsset.Object);
    else UE_LOG(LogTemp, Warning, TEXT("MeshAsset(Sparky) failed."));

    static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(TEXT("Material'/Game/sparkyHMaterial.sparkyHMaterial'"));
    if (MaterialAsset.Succeeded()) CubicleMaterial = MaterialAsset.Object;
    else UE_LOG(LogTemp, Warning, TEXT("MaterialAsset(Sparky) failed."));

    static ConstructorHelpers::FObjectFinder<UMaterialInterface> HighlightedAsset(TEXT("Material'/Game/sparkyTMaterial.sparkyTMaterial'"));
    if (HighlightedAsset.Succeeded()) CubicleHMaterial = HighlightedAsset.Object;
    else UE_LOG(LogTemp, Warning, TEXT("HighlightedAsset(Sparky) failed."));

    bIsSelected = false;

    ToggleMaterial();

    SetActorScale3D(FVector(1.5f, 1.5f, 1.0f));
}