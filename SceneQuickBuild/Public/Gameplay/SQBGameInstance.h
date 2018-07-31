// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BaseActor.h"
#include "SQBGameInstance.generated.h"

/**
 *  ��ϷInstance�࣬����BaseActor֮���ͨ��,��ͨ�ŵ��м���
 */
UCLASS()
class SCENEQUICKBUILD_API USQBGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	USQBGameInstance();
	
public:
	/** ע��BaseActor���Ա��໥֮���ͨ��*/
	void RegisterBaseActor(class ABaseActor* InRef);

private:
	TArray<class ABaseActor*> AllBaseActor;
	
};
