// Fill out your copyright notice in the Description page of Project Settings.

#include "FlightPlatform.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"
#include "Common/OriginHelper.h"
#include "Camera/CameraComponent.h"
#include "ConstructorHelpers.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/PlayerInput.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/BoxComponent.h"


AFlightPlatform::AFlightPlatform(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer.SetDefaultSubobjectClass<UFloatingPawnMovement>(TEXT("ModuleMovement")))
{
	PlaneCapsule = CreateDefaultSubobject<UBoxComponent>(TEXT("PlaneCollision"));
	PlaneCapsule->SetupAttachment(BaseScene);
	PlaneCapsule->SetBoxExtent(FVector(100.f, 46.f, 22.f));
	PlaneCapsule->SetCollisionResponseToAllChannels(ECR_Block);
	RootComponent = PlaneCapsule;

	PlaneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaneMesh"));
	PlaneMesh->SetupAttachment(PlaneCapsule);
	PlaneMesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	PlaneMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	PlaneMesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	PlaneMesh->SetRelativeLocation(FVector(0.f, 0.f, -20.f));
	
	ModuleMovement->SetUpdatedComponent(PlaneCapsule);
	ViewCamera->SetupAttachment(PlaneMesh, TEXT("CameraSocket"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshFinder(TEXT("/Game/Plane/CGModel/F18C/F-18C_Hornet"));
	if (!ensure(MeshFinder.Succeeded()))return;
	PlaneMesh->SetStaticMesh(MeshFinder.Object);
	PlatformType = EPlatformCategory::EPlane;

	PlatformData.ID = TEXT("Plane");
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

void AFlightPlatform::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//设置飞行平台额外交互方式
	//飞机向上或向下
	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("FlyPlatformUp", EKeys::Up, 1.f));
	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("FlyPlatformUp", EKeys::Down, -1.f));

	PlayerInputComponent->BindAxis(TEXT("FlyPlatformUp"), this, &AFlightPlatform::MoveUp);
}

void AFlightPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddMovementInput(GetActorRotation().Vector());
	SetMaxSpeed(FlySpeed*DeltaTime);
	OriginHelper::Debug_ScreenMessage(FString::SanitizeFloat(GetToCenterSubAngle()));

	if (FlySpeed < 10000.f)return;
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

void AFlightPlatform::BeginDestroy()
{
	Super::BeginDestroy();
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
	FlySpeed += 1000 * Val;

	//Super::Implementation_MoveForward(Val * 200.f);
}

void AFlightPlatform::Implementation_MoveRight(float Val)
{
	float DeltaTime = GetWorld()->GetDeltaSeconds();

	if (Val != 0.f)
	{
		FRotator PlaneRot = GetActorRotation();
		const FQuat AddedAngle_Yaw(FVector(0.f,0.f,1.f), Val * FMath::DegreesToRadians(DeltaTime*20.f));

		AddActorWorldRotation(AddedAngle_Yaw);
		if (CurOffsetAngle_Right >= -30.f && CurOffsetAngle_Right <= 30.f)
		{
			float DeltaAngle = Val * DeltaTime * 30.f * 1.5f;
			if (CurOffsetAngle_Right + DeltaAngle > 30.f)
				DeltaAngle = 30 - CurOffsetAngle_Right;
			else if (CurOffsetAngle_Right + DeltaAngle < -30.f)
				DeltaAngle = -30.f - CurOffsetAngle_Right;
			PlaneRot = GetActorRotation();
			const FQuat AddedAngle_Roll(FRotationMatrix(PlaneRot).GetUnitAxis(EAxis::X), -FMath::DegreesToRadians(DeltaAngle));
			AddActorWorldRotation(AddedAngle_Roll);
			CurOffsetAngle_Right += DeltaAngle;
		}
	}
	else
	{
		if (CurOffsetAngle_Right != 0.f)
		{
			CurOffsetAngle_Right = GetToCenterSubAngle();
			FRotator PlaneRot = GetActorRotation();
			float DeltaAngle = DeltaTime * (CurOffsetAngle_Right > 0.f ? -30.f : 30.f) * 1.5f;
			const float Tmp = CurOffsetAngle_Right + DeltaAngle;
			if (CurOffsetAngle_Right*Tmp <= 0.f)
			{
				DeltaAngle = 0.f - CurOffsetAngle_Right;
				CurOffsetAngle_Right = 0.f;
			}
			else
				CurOffsetAngle_Right = Tmp;
			const FQuat AddedAngle_Yaw(FRotationMatrix(PlaneRot).GetUnitAxis(EAxis::X), -FMath::DegreesToRadians(DeltaAngle));
			AddActorWorldRotation(AddedAngle_Yaw);
		}
	}
}

void AFlightPlatform::MoveUp(float Val)
{
	//if (FlySpeed < 40000)return;
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	
	//if (Val != 0 && CurOffsetAngle_Up <= 40.f && CurOffsetAngle_Up >= -40.f)
	//{
	//	float DeltaAngle = Val * DeltaTime * 20.f;
	//	
	//	if (CurOffsetAngle_Up + DeltaAngle > 40.f)
	//	{
	//		DeltaAngle = 40.f - CurOffsetAngle_Up;
	//	}
	//	else if (CurOffsetAngle_Up + DeltaAngle < -40.f)
	//	{
	//		DeltaAngle = -40.f - CurOffsetAngle_Up;
	//	}
	//	//OriginHelper::Debug_ScreenMessage(FString::SanitizeFloat(DeltaAngle));
	//
	//}
	float DeltaAngle = Val * DeltaTime * 30.f;
	const FQuat AddedAngle_Pitch(FRotationMatrix(GetActorRotation()).GetUnitAxis(EAxis::Y), -FMath::DegreesToRadians(DeltaAngle));
	CurOffsetAngle_Up += DeltaAngle;
	AddActorWorldRotation(AddedAngle_Pitch);
}

void AFlightPlatform::UpdatePlatformData()
{
	Super::UpdatePlatformData();

	const FVector TargetDir = PlatformData.PlatformPos - GetActorLocation();
	const FVector PlainDir = GetActorRotation().Vector();

}

int32 AFlightPlatform::EventTest(float Speed, int32 Num)
{
	return Num;
}

FVector AFlightPlatform::GetUpVector()
{ 
	FVector Up = FRotationMatrix(GetActorRotation()).GetUnitAxis(EAxis::Z);
	DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + Up * 200, FColor::Green, false, 20.f, 0, 2.f);
	const FQuat Temp = FQuat(FRotationMatrix(GetActorRotation()).GetUnitAxis(EAxis::X), FMath::DegreesToRadians(CurOffsetAngle_Right*1.5f));
	Up = Temp.RotateVector(Up);
	
	DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + Up * 200, FColor::Black, false, 5.f, 0, 2.f);
	return Up;
}

float AFlightPlatform::GetToCenterSubAngle()
{
	const FMatrix PlainRotationMat = FRotationMatrix(GetActorRotation());
	const FVector PlainUp = PlainRotationMat.GetUnitAxis(EAxis::Z);
	const FVector PlainRight = PlainRotationMat.GetUnitAxis(EAxis::Y);
	const FVector PlainForward = PlainRotationMat.GetUnitAxis(EAxis::X);

	const FVector PlaneNormal = FVector::CrossProduct(PlainForward, FVector(0.f, 0.f, 1.f));
	const FPlane CenterPlane(FVector::ZeroVector, PlaneNormal);

	float SubAngle = FMath::RadiansToDegrees(FMath::Acos(CenterPlane.PlaneDot(PlainUp)));
	return SubAngle - 90.f;
}
