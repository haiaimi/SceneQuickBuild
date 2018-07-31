// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BaseActor.h"
#include "SQBGameInstance.generated.h"

/**
 *  游戏Instance类，用于BaseActor之间的通信,是通信的中间类
 */
UCLASS()
class SCENEQUICKBUILD_API USQBGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	USQBGameInstance();
	
public:
	/** 注册BaseActor，以便相互之间的通信*/
	void RegisterBaseActor(class ABaseActor* InRef);

private:
	TArray<class ABaseActor*> AllBaseActor;
	
};
