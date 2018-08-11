// Fill out your copyright notice in the Description page of Project Settings.

#include "SQBGameInstance.h"
#include "OriginHelper.h"
#include "BaseActor.h" 


USQBGameInstance::USQBGameInstance():
	CommunicationManager(nullptr)
{
	
}

void USQBGameInstance::StartGameInstance()
{
	if (CommunicationManager == nullptr)
		CommunicationManager = NewObject<UCommunicationManager>(this);

	CommunicationManager->BreakCommunication(nullptr, nullptr, FString(TEXT("SendID")));

	Super::StartGameInstance();
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

void USQBGameInstance::SendPosInfo_Implementation(ABaseActor* Sender, void* InParams)
{
	FSendPosInfo Temp;
	if (InParams)
	{
		Temp.PlatformPos = Sender->GetActorLocation() + Sender->GetActorRotation().Vector()*100.f;
	}

	Sender->SendPosInfo_Publish(&Temp);
}

