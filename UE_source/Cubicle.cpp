// Fill out your copyright notice in the Description page of Project Settings.


#include "Cubicle.h"

// Sets default values
ACubicle::ACubicle()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Models/box.box'"));
	if (MeshAsset.Succeeded()) MeshComponent->SetStaticMesh(MeshAsset.Object);
	else UE_LOG(LogTemp, Warning, TEXT("MeshAsset(Box) failed."));

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(TEXT("/Script/Engine.Material'/Game/Materials/boxMaterial.boxMaterial'"));
	if (MaterialAsset.Succeeded()) MeshComponent->SetMaterial(0, MaterialAsset.Object);
	else UE_LOG(LogTemp, Warning, TEXT("MaterialAsset(Box) failed."));

	SetActorScale3D(FVector(1.0f, 1.0f, 1.0f));

}

// Called when the game starts or when spawned
void ACubicle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACubicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACubicle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

