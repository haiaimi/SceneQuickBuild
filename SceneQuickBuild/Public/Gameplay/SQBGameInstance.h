// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
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

	template<class T>
	bool SpawnSQBActor(UClass* InClass, FVector const* Location = NULL, FRotator const* Rotation = NULL, const FActorSpawnParameters& SpawnParameters = FActorSpawnParameters())
	{
		T* SpawnedActor = GetWorld()->SpawnActor<T>(Location, Rotation, SpawnParameters);
		if (SpawnedActor)
		{
			if (SpawnedActor->GetClass()->IsChildOf(ABaseActor::StaticClass()))
			{
				RegisterBaseActor(SpawnedActor);
				return true;
			}
		}
		return false;      //生成失败
	}
	
	/**获取所有BaseActor的ID名*/
	TArray<FName> GetData_AllOtherName(FName& PlatformID, class ABaseActor* ActorRef);

private:
	TArray<class ABaseActor*> AllBaseActor;
};
