// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CommunicationManager.generated.h"

/**
 *  通信管理类，控制场景中所有物体的通信关系
 */
UCLASS()
class SCENEQUICKBUILD_API UCommunicationManager : public UObject
{
	GENERATED_BODY()
	
public:
	UCommunicationManager();

public:
	/** 构建SQBActor之间的通信*/
	void BuildCommunication(class ABaseActor* PublishActor, class ABaseActor* SubscribeActor, FString& FunName);
};
