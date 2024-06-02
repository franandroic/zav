// Fill out your copyright notice in the Description page of Project Settings.


#include "BirdCamera.h"

// Sets default values
ABirdCamera::ABirdCamera()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	RootComponent = CameraComponent;

	CameraComponent->SetFieldOfView(90.0f);

}

// Called when the game starts or when spawned
void ABirdCamera::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABirdCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UCameraComponent* ABirdCamera::GetCameraComponent()
{
	return CameraComponent;
}

