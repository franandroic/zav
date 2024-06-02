// Fill out your copyright notice in the Description page of Project Settings.


#include "CubicleBox.h"

ACubicleBox::ACubicleBox()
{
    bIsSparky = false;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Models/box.box'"));
    if (MeshAsset.Succeeded()) MeshComponent->SetStaticMesh(MeshAsset.Object);
    else UE_LOG(LogTemp, Warning, TEXT("MeshAsset(Box) failed."));

    static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(TEXT("/Script/Engine.Material'/Game/Materials/boxMaterial.boxMaterial'"));
    if (MaterialAsset.Succeeded()) CubicleMaterial = MaterialAsset.Object;
    else UE_LOG(LogTemp, Warning, TEXT("MaterialAsset(Box) failed."));

    static ConstructorHelpers::FObjectFinder<UMaterialInterface> HighlightedAsset(TEXT("/Script/Engine.Material'/Game/Materials/boxHMaterial.boxHMaterial'"));
    if (HighlightedAsset.Succeeded()) CubicleHMaterial = HighlightedAsset.Object;
    else UE_LOG(LogTemp, Warning, TEXT("HighlightedAsset(Box) failed."));

    bIsSelected = false;

	ToggleMaterial();

	SetActorScale3D(FVector(1.0f, 1.0f, 1.0f));
}