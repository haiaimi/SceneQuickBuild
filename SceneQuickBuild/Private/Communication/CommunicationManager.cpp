// Fill out your copyright notice in the Description page of Project Settings.

#include "CommunicationManager.h"




UCommunicationManager::UCommunicationManager()
{

}

void UCommunicationManager::BuildCommunication(class ABaseActor* PublishActor, class ABaseActor* SubscribeActor)
{
	FUNC_DECLARE_DELEGATE(FDelegate1, void, int);
	FUNC_DECLARE_DELEGATE(FDelegate2, void, int);

	FDelegate2 a;
	FDelegate1 b;

	a = b;
}
