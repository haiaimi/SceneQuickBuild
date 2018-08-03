// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
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
	void RegisterSQBActor(class ABaseActor* InRef);

	/** ע���б��д��ڵ�Actor����ʱ��Actor�ѱ��ݻٻ��߲�����ͨ�Ž���*/
	void UnRegisterSQBActor(class ABaseActor* InRef);

	template<class T>
	bool SpawnSQBActor(UClass* InClass, FVector const* Location = NULL, FRotator const* Rotation = NULL, const FActorSpawnParameters& SpawnParameters = FActorSpawnParameters())
	{
		T* SpawnedActor = GetWorld()->SpawnActor<T>(Location, Rotation, SpawnParameters);
		if (SpawnedActor)
		{
			if (SpawnedActor->GetClass()->IsChildOf(ABaseActor::StaticClass()))
			{
				RegisterSQBActor(SpawnedActor);
				return true;
			}
		}
		return false;      //����ʧ��
	}
	
	/** ��ȡ����BaseActor��ID��*/
	TArray<FName> GetData_AllOtherName(FName& PlatformID, class ABaseActor* ActorRef);

private:
	TArray<class ABaseActor*> AllSQBActor;

	/**����SQBActor��ص�����*/
	TArray<struct FPlatformData*> AllSQBData;
};
