// Fill out your copyright notice in the Description page of Project Settings.


#include "SparkyPlayer.h"

// Sets default values
ASparkyPlayer::ASparkyPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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