// Fill out your copyright notice in the Description page of Project Settings.

#include "SQBGameInstance.h"
#include "BaseActor.h"
#include "OriginHelper.h"

USQBGameInstance::USQBGameInstance()
{
	
}

void USQBGameInstance::RegisterSQBActor(class ABaseActor* InRef)
{
	AllSQBActor.Add(InRef);
}

void USQBGameInstance::UnRegisterSQBActor(class ABaseActor* InRef)
{
	
}

TArray<FName> USQBGameInstance::GetData_AllOtherName(FName& PlatformID, class ABaseActor* ActorRef)
{
	TArray<FName> Result;
	for (auto Iter : AllSQBActor)
	{
		Result.Add(Iter->GetPlatformData().ID);
	}

	return Result;
}

void USQBGameInstance::SendPosInfo(ABaseActor* Sender, ABaseActor* Receiver)
{
	FSendPosInfo Param;
	Sender->BindSendPosInfo(Receiver);
}

