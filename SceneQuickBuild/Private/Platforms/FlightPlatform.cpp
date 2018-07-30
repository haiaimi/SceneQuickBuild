// Fill out your copyright notice in the Description page of Project Settings.

#include "FlightPlatform.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"
#include "Common/OriginHelper.h"
#include "Camera/CameraComponent.h"
#include "ConstructorHelpers.h"
#include "GameFramework/PawnMovementComponent.h"


AFlightPlatform::AFlightPlatform()
{
	PlaneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaneMesh"));
	PlaneMesh->SetupAttachment(BaseScene);
	PlaneMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	PlaneMesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	ModuleMovement->SetUpdatedComponent(BaseScene);
	ViewCamera->SetupAttachment(PlaneMesh, TEXT("CameraSocket"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshFinder(TEXT("/Game/Plane/CGModel/F18C/F-18C_Hornet"));
	if (!ensure(MeshFinder.Succeeded()))return;
	PlaneMesh->SetStaticMesh(MeshFinder.Object);
	//PlatformMovementComponent = CreateDefaultSubobject<UMovementComponent>(TEXT("PlatformMovementComponent"));
	//PlatformMovementComponent->SetUpdatedComponent(PlaneMesh);
}

void AFlightPlatform::BeginPlay()
{
	Super::BeginPlay();

	//测试序列化
	TArray<int32>  EnumsResult = { 0,1,2,3 };
	FVector Pos(10.1f, 10.1f, 10.1f);
	//序列化的顺序就是根据下面的顺序
	OriginHelper::SerializeNumber(TEXT("TEST"), 10.f);
	OriginHelper::SerializeVector(TEXT("Position"), Pos);
	SerializeEnumsToJson(TEXT("PlaneModlues"), EPlatformModule, EnumsResult);
	OriginHelper::FinishSerizlize(TEXT("Test.json"));
	OriginHelper::ResetJson();
}

void AFlightPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 飞机飞行时的晃动，提高真实性
	static float ShakeTime = 0.f;
	static float AddDir = 1.f;
	if (ShakeTime > PI)
	{
		ShakeTime = PI;
		AddDir = -1.f;
	}
	if (ShakeTime < -PI)
	{
		ShakeTime = -PI;
		AddDir = 1.f;
	}
	const float CurRelHeight = FMath::Sin(ShakeTime + PI)*AddDir;
	ViewCamera->SetRelativeLocation(FVector(0.f, ShakeTime * 0.7f, CurRelHeight)*2.f);

	ShakeTime += DeltaTime * AddDir;
}

void AFlightPlatform::UpdateCommunicateType()
{
	//根据不同的通信模式，选择不同的模拟方式
	switch (CommunicateType)
	{
		//TCP/UDP
	case EOutsideCommunicate::EUDP_TCP:
		break;
		
		//手动控制
	case EOutsideCommunicate::EManualControl:
		break;

		//读取Json文件
	case EOutsideCommunicate::ELoadConfigFile_Json:
		break;

		//读取xml文件
	case EOutsideCommunicate::ELoadConfigFile_Xml:
		break;
	}
}

void AFlightPlatform::SetToTCP_UDPMode()
{

}

void AFlightPlatform::SetToManualControlMode()
{

}

void AFlightPlatform::SetToJsonMode()
{
	//从飞行平台的配置文件中读取数据
	TArray<int32>  EnumsResult;
	OriginHelper::PrepareJson(FlightConfigName);
	OriginHelper::GetNumberFromJson(FlightConfigName, TEXT("FlySpeed"), 0, FlySpeed);
	OriginHelper::GetNumberFromJson(FlightConfigName, TEXT("FlyAccleration"), 1, FlyAcceleration);
	OriginHelper::GetVectorFromJson(FlightConfigName, TEXT("FlyLocation"), 2, FlyLocation);
	EnumsFromJson(FlightConfigName, TEXT("FlightModules"), EPlatformModule, 3, EnumsResult);
	OriginHelper::ResetJson();   //清空单例中的数据以便下次数据读取写入
}

void AFlightPlatform::SetToXmlMode()
{

}

void AFlightPlatform::Implementation_MoveForward(float Val)
{
	Super::Implementation_MoveForward(Val * 200.f);
}

void AFlightPlatform::Implementation_MoveRight(float Val)
{
	static bool bRotated = false;
	FRotator PlaneRot = GetActorRotation();
	
	//在转弯时机身适当倾斜
	if (Val > 0 && !bRotated)
	{
		bRotated = true;
		FRotator PlaneRot = GetActorRotation();
		//this->AddActorWorldRotation()
	
		PlaneRot.Roll += 30.f;
		SetActorRotation(PlaneRot);
	}
	else
	{

	}

	Super::Implementation_MoveRight(Val * 200.f);
}

void AFlightPlatform::EventTest()
{
	OriginHelper::Debug_ScreenMessage(TEXT("按下"), 5);
}
