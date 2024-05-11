// Fill out your copyright notice in the Description page of Project Settings.


#include "SparkyPlayer.h"

// Sets default values
ASparkyPlayer::ASparkyPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Models/sparky.sparky'"));
	if (MeshAsset.Succeeded()) MeshComponent->SetStaticMesh(MeshAsset.Object);
	else UE_LOG(LogTemp, Warning, TEXT("MeshAsset(Sparky) failed."));

	bIsSelected = false;

	ToggleMaterial();

	SetActorScale3D(FVector(1.0f, 1.0f, 1.0f));

}

// Called when the game starts or when spawned
void ASparkyPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASparkyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASparkyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASparkyPlayer::ToggleMaterial()
{
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(TEXT("/Script/Engine.Material'/Game/Materials/sparkyMaterial.sparkyMaterial'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> HighlightedAsset(TEXT("/Script/Engine.Material'/Game/Materials/sparkyHMaterial.sparkyHMaterial'"));

	if (!bIsSelected) {
		if (MaterialAsset.Succeeded()) MeshComponent->SetMaterial(0, MaterialAsset.Object);
		else UE_LOG(LogTemp, Warning, TEXT("MaterialAsset(Sparky) failed."));
	} else {
		if (HighlightedAsset.Succeeded()) MeshComponent->SetMaterial(0, HighlightedAsset.Object);
		else UE_LOG(LogTemp, Warning, TEXT("HighlightedAsset(Sparky) failed."));
	}
}