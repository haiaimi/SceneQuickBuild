// Fill out your copyright notice in the Description page of Project Settings.

#include "SQBGameInstance.h"




USQBGameInstance::USQBGameInstance()
{

}

void USQBGameInstance::RegisterBaseActor(class ABaseActor* InRef)
{
	AllBaseActor.Add(InRef);
}
