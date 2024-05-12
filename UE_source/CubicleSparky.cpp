// Fill out your copyright notice in the Description page of Project Settings.


#include "CubicleSparky.h"

ACubicleSparky::ACubicleSparky()
{
    bIsSparky = true;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Models/sparky.sparky'"));
    if (MeshAsset.Succeeded()) MeshComponent->SetStaticMesh(MeshAsset.Object);
    else UE_LOG(LogTemp, Warning, TEXT("MeshAsset(Sparky) failed."));

    static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(TEXT("/Script/Engine.Material'/Game/Materials/sparkyMaterial.sparkyMaterial'"));
    if (MaterialAsset.Succeeded()) CubicleMaterial = MaterialAsset.Object;
    else UE_LOG(LogTemp, Warning, TEXT("MaterialAsset(Sparky) failed."));

    static ConstructorHelpers::FObjectFinder<UMaterialInterface> HighlightedAsset(TEXT("/Script/Engine.Material'/Game/Materials/sparkyHMaterial.sparkyHMaterial'"));
    if (HighlightedAsset.Succeeded()) CubicleHMaterial = HighlightedAsset.Object;
    else UE_LOG(LogTemp, Warning, TEXT("HighlightedAsset(Sparky) failed."));

    bIsSelected = false;

	ToggleMaterial();

	SetActorScale3D(FVector(1.0f, 1.0f, 1.0f));
}