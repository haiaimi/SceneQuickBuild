// Fill out your copyright notice in the Description page of Project Settings.

#include "SceneQuickBuildGameModeBase.h"
#include "Gameplay/PlatformController.h"
#include "FlightPlatform.h"
#include "GameFramework/DefaultPawn.h"
#include "GameFramework/SpectatorPawn.h"




ASceneQuickBuildGameModeBase::ASceneQuickBuildGameModeBase()
{
	PlayerControllerClass = APlatformController::StaticClass();
	DefaultPawnClass = ASpectatorPawn::StaticClass();
}
