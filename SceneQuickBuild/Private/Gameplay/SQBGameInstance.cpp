// Fill out your copyright notice in the Description page of Project Settings.

#include "SQBGameInstance.h"
#include "BaseActor.h"
#include "OriginHelper.h"

USQBGameInstance::USQBGameInstance()
{
	
}

void USQBGameInstance::RegisterBaseActor(class ABaseActor* InRef)
{
	AllBaseActor.Add(InRef);
}

TArray<FName> USQBGameInstance::GetData_AllOtherName(FName& PlatformID, class ABaseActor* ActorRef)
{
	TArray<FName> Result;
	for (auto Iter : AllBaseActor)
	{
		Result.Add(Iter->GetPlatformData().ID);
	}

	return Result;
}

