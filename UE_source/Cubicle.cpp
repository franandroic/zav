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

	bIsSelected = false;

	ToggleMaterial();

	SetActorScale3D(FVector(1.0f, 1.0f, 1.0f));
}

// Called when the game starts or when spawned
void ACubicle::BeginPlay()
{
	Super::BeginPlay();
	
	bIsMoving = false;
}

// Called every frame
void ACubicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UE_LOG(LogTemp, Warning, TEXT("%d"), bIsMoving);

	if (bIsMoving) {

		FVector locationIncrement = GetActorLocation() + MoveDirection * 4000.0f * DeltaTime;
		SetActorLocation(locationIncrement);

		//UE_LOG(LogTemp, Warning, TEXT("A: %f %f %f, B: %f %f %f"), GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z, MoveEndLocation.X, MoveEndLocation.Y, MoveEndLocation.Z);

		if ((GetActorLocation() - MoveEndLocation).Size() < 50.0f) {
			bIsMoving = false;
			SetActorLocation(MoveEndLocation);
			if (MoveEndLocation.Z == 121.1f) Destroy();
		}

	}

}

// Called to bind functionality to input
void ACubicle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACubicle::ToggleMaterial()
{
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(TEXT("/Script/Engine.Material'/Game/Materials/boxMaterial.boxMaterial'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> HighlightedAsset(TEXT("/Script/Engine.Material'/Game/Materials/boxHMaterial.boxHMaterial'"));

	if (!bIsSelected) {
		if (MaterialAsset.Succeeded()) MeshComponent->SetMaterial(0, MaterialAsset.Object);
		else UE_LOG(LogTemp, Warning, TEXT("MaterialAsset(Box) failed."));
	} else {
		if (HighlightedAsset.Succeeded()) MeshComponent->SetMaterial(0, HighlightedAsset.Object);
		else UE_LOG(LogTemp, Warning, TEXT("HighlightedAsset(Box) failed."));
	}
}

void ACubicle::SlideMove(FVector EndLocation)
{
	if (!bIsMoving) {
		MoveEndLocation = EndLocation;
		MoveDirection = (MoveEndLocation - GetActorLocation()).GetSafeNormal();
		bIsMoving = true;
	}
}