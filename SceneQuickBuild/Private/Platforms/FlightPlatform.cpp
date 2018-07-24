// Fill out your copyright notice in the Description page of Project Settings.

#include "FlightPlatform.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"


AFlightPlatform::AFlightPlatform()
{
	PlaneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaneMesh"));
}

void AFlightPlatform::BeginPlay()
{
	//测试枚举与字符串之间的转换
	/*UEnum* Test = FindObject<UEnum>(ANY_PACKAGE, TEXT("EPlatformModule"));
	int32 i = Test->GetValueByNameString(TEXT("ERadar"));
	GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Black, FString::FormatAsNumber(i));*/
}

void AFlightPlatform::Tick(float DeltaTime)
{
	
}

void AFlightPlatform::UpdateCommunicateType()
{
	//根据不同的通信模式，选择不同的模拟方式
	switch (CommunicateType)
	{
	case EOutsideCommunicate::EUDP_TCP:
		break;
		
	case EOutsideCommunicate::EManualControl:
		break;

	case EOutsideCommunicate::ELoadConfigFile_Json:
		break;

	case EOutsideCommunicate::ELoadConfigFile_Xml:
		break;
	}
}

