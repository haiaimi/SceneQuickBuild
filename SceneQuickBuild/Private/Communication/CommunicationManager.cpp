// Fill out your copyright notice in the Description page of Project Settings.

#include "CommunicationManager.h"
#include "BaseActor.h"


UCommunicationManager::UCommunicationManager()
{
	//ABaseActor::MyStruct A;
	//FWH_FUN B;
}

void UCommunicationManager::BuildCommunication(class ABaseActor* PublishActor, class ABaseActor* SubscribeActor)
{
	FUNC_DECLARE_DELEGATE(FDelegate1, void, int, float);
	FUNC_DECLARE_DELEGATE(FDelegate2, float, int, float);

	FDelegate2 a;
	FDelegate1 b;
	if(a.IsBound())
	{
		a.Execute(10, 10);
	}
	//TPair<ABaseActor::MyStruct,UFunction*>
}
