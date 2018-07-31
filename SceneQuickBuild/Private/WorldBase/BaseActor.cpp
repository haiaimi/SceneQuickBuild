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
}

void ABaseActor::BeginPlay()
{
	Super::BeginPlay();

	//更新通信状态，执行对应通信状态的方法
	UpdateCommunicateType();   
	//DECLARE_MULTICAST_DELEGATE
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

