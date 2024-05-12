// Fill out your copyright notice in the Description page of Project Settings.


#include "Floor.h"

// Sets default values
AFloor::AFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Models/floor.floor'"));
	if (MeshAsset.Succeeded()) MeshComponent->SetStaticMesh(MeshAsset.Object);
	else UE_LOG(LogTemp, Warning, TEXT("MeshAsset(Floor) failed."));

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(TEXT("/Script/Engine.Material'/Game/Materials/floorMaterial.floorMaterial'"));
	if (MaterialAsset.Succeeded()) MeshComponent->SetMaterial(0, MaterialAsset.Object);
	else UE_LOG(LogTemp, Warning, TEXT("MaterialAsset(Floor) failed."));

	SetActorScale3D(FVector(1.0f, 1.0f, 1.0f));

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> EndpointMaterialAsset(TEXT("/Script/Engine.Material'/Game/Materials/endpointMaterial.endpointMaterial'"));
	if (EndpointMaterialAsset.Succeeded()) EndpointMaterial = EndpointMaterialAsset.Object;
	else UE_LOG(LogTemp, Warning, TEXT("EndpointMaterialAsset(Floor) failed."));
}

// Called when the game starts or when spawned
void AFloor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFloor::ApplyEndpointMaterial()
{
	if (EndpointMaterial) MeshComponent->SetMaterial(0, EndpointMaterial);
}