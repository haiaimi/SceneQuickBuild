// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/PlatformController.h"

// Sets default values
APlatformController::APlatformController()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlatformController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlatformController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlatformController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

