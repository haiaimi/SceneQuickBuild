// Fill out your copyright notice in the Description page of Project Settings.
#include "Public/WorldBase/BaseActor.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerInput.h"

ABaseActor::ABaseActor():
	CommunicateType(EOutsideCommunicate::ELoadConfigFile_Json),    //默认是读取Json文件的方式
	OwnerPltform(nullptr),
	PlatformType(EPlatformCategory::EBaseModule)
{
	PrimaryActorTick.bCanEverTick = true;
	ModuleMovement = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>(TEXT("ModuleMovement"));
	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	BaseScene = CreateDefaultSubobject<USceneComponent>(TEXT("BaseScene"));
	ViewCamera->SetupAttachment(BaseScene);
	PlatformData = new struct FPlatformData;
	PlatformData->ID = TEXT("Base");
}

void ABaseActor::BeginPlay()
{
	Super::BeginPlay();

	//更新通信状态，执行对应通信状态的方法
	UpdateCommunicateType();   

	WH_TEST1(5, 10, 20, 40, 50)
	int32 ArgCount = WH_ARG_COUNT(float, int, double, bool);
	OriginHelper::Debug_ScreenMessage(FString::FormatAsNumber(i));
	OriginHelper::Debug_ScreenMessage(FString::FormatAsNumber(j));
	OriginHelper::Debug_ScreenMessage(FString::FormatAsNumber(ArgCount));
}

void ABaseActor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	//设置基础模块的玩家输入响应
	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("BaseMoveForward", EKeys::W, 1.f));
	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("BaseMoveForward", EKeys::S, -1.f));
	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("BaseMoveRight", EKeys::D, 1.f));
	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("BaseMoveRight", EKeys::A, -1.f));

	PlayerInputComponent->BindAxis(TEXT("BaseMoveForward"), this, &ABaseActor::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("BaseMoveRight"), this, &ABaseActor::MoveRight);
}

void ABaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseActor::BeginDestroy()
{
	Super::BeginDestroy();

	delete PlatformData;
	PlatformData = nullptr; 
}

void ABaseActor::SetCommunicateType(EOutsideCommunicate::Type InType)
{
	CommunicateType = InType;
	//更新通信模式，不同的模块会重写不同的方法
	UpdateCommunicateType();  
}

void ABaseActor::SetMaxSpeed(float InSpeed)
{
	UFloatingPawnMovement* CurMovement = Cast<UFloatingPawnMovement>(ModuleMovement);
	CurMovement->MaxSpeed = InSpeed;
}

void ABaseActor::MoveForward(float Val)
{
	Implementation_MoveForward(Val);
}

void ABaseActor::MoveRight(float Val)
{
	Implementation_MoveRight(Val);
}

void ABaseActor::Implementation_MoveForward(float Val)
{
	AddMovementInput(GetControlRotation().Vector(), Val);
}

void ABaseActor::Implementation_MoveRight(float Val)
{
	FRotator ControlRot = GetControlRotation();
	AddMovementInput(FRotationMatrix(ControlRot).GetUnitAxis(EAxis::Y), Val);
}

void ABaseActor::SetPlatformData(FName InID, ESQBTeam::Type InTeam)
{
	PlatformData->ID = InID;
	PlatformData->OwnerTeam = InTeam;
	FString::Printf(TEXT(""), 1);
}

void ABaseActor::WH_FFUN(float speed,int num)
{

}