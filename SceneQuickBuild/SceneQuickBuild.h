// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogOrigin, Log, All);

class FSceneQuickBuildModule :public FDefaultGameModuleImpl
{
public:
	virtual void StartupModule()override;
};