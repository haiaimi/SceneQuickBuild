// Fill out your copyright notice in the Description page of Project Settings.

#include "CommunicationManager.h"
#include "BaseActor.h"


UCommunicationManager::UCommunicationManager()
{
	
}

void UCommunicationManager::BuildCommunication(class ABaseActor* PublishActor, class ABaseActor* SubscribeActor, FString& FunName)
{
	if (BindFunctionPtr* FindRes = GlobalBindFunctions.Find(FName(*FunName)))
	{
		(PublishActor->**FindRes)(SubscribeActor);   //执行该函数指针，进行绑定
	}
}
