// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "SceneQuickBuildType.h"
#include "CommunicationManager.h"
#include "SQBGameInstance.generated.h"

class ABaseActor;
class UCommunicationManager;

/**
 *  ��ϷInstance�࣬����BaseActor֮���ͨ��,��ͨ�ŵ��м���
 */
UCLASS()
class SCENEQUICKBUILD_API USQBGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	USQBGameInstance();

	virtual void StartGameInstance()override;
	
public:
	/** ע��BaseActor���Ա��໥֮���ͨ��*/
	void RegisterSQBActor(ABaseActor* InRef);

	/** ע���б��д��ڵ�Actor����ʱ��Actor�ѱ��ݻٻ��߲�����ͨ�Ž���*/
	void UnRegisterSQBActor(ABaseActor* InRef);

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
	TArray<FName> GetData_AllOtherName(FName& PlatformID, ABaseActor* ActorRef);

	void SendPosInfo(ABaseActor* Sender, ABaseActor* Receiver);
	 
	WH_COMMUNICATE_IMPLEMENT(SendPosInfo);
	
public:

private:
	TArray<ABaseActor*> AllSQBActor;

	/**����SQBActor��ص�����*/
	TArray<struct FPlatformData*> AllSQBData;

	/**�ڲ�ͨ�Ź�����*/
	UCommunicationManager* CommunicationManager;
};