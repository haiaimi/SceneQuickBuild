// Fill out your copyright notice in the Description page of Project Settings.

#include "SceneQuickBuild.h"
#include "Modules/ModuleManager.h"
#include "Public/Common/OriginHelper.h"

DEFINE_LOG_CATEGORY(LogOrigin)

void FSceneQuickBuildModule::StartupModule()
{
	OriginHelper::Init(FString(TEXT("ConfigRes/FlightPlatform")));
}


IMPLEMENT_PRIMARY_GAME_MODULE( FSceneQuickBuildModule, SceneQuickBuild, "SceneQuickBuild" );

