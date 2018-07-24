// Fill out your copyright notice in the Description page of Project Settings.
#include "Public/WorldBase/BaseActor.h"

ABaseActor::ABaseActor():
	CommunicateType(EOutsideCommunicate::ELoadConfigFile_Json),    //默认是读取Json文件的方式
	OwnerPltform(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;

}

void ABaseActor::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseActor::SetCommunicateType(EOutsideCommunicate::Type InType)
{
	CommunicateType = InType;
	//更新通信模式，不同的模块会重写不同的方法
	UpdateCommunicateType();  
}

