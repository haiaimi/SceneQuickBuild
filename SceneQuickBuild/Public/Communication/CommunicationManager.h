// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CommunicationManager.generated.h"

/**
 *  ͨ�Ź����࣬���Ƴ��������������ͨ�Ź�ϵ
 */
UCLASS()
class SCENEQUICKBUILD_API UCommunicationManager : public UObject
{
	GENERATED_BODY()
	
public:
	UCommunicationManager();

public:
	/** ����SQBActor֮���ͨ��*/
	void BuildCommunication(class ABaseActor* PublishActor, class ABaseActor* SubscribeActor, FString& FunName);
};
