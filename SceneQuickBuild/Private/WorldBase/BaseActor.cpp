// Fill out your copyright notice in the Description page of Project Settings.
#include "Public/WorldBase/BaseActor.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerInput.h"

TArray<UFunction*> GlobalModuleFunctions = { nullptr };
TMap<FName, BindFunctionPtr> GlobalBindFunctions = {};
TMap<FName, RemoveDelegatePtr> GlobalRemoveDelegates = {};
typedef void(*funPtr)(int32, int32);

ABaseActor::ABaseActor(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer),
	CommunicateType(EOutsideCommunicate::ELoadConfigFile_Json),    //默认是读取Json文件的方式
	OwnerPltform(nullptr),
	PlatformType(EPlatformCategory::EBaseModule)
{
	PrimaryActorTick.bCanEverTick = true;
	ModuleMovement = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>(TEXT("ModuleMovement"));
	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	BaseScene = CreateDefaultSubobject<USceneComponent>(TEXT("BaseScene"));
	ViewCamera->SetupAttachment(BaseScene);
	PlatformData = new FBaseActorData;
}

void ABaseActor::BeginPlay()
{
	Super::BeginPlay();

	//更新通信状态，执行对应通信状态的方法
	UpdateCommunicateType();   

	//WH_TEST1(5, 10, 20, 40, 50)
	//int32 ArgCount = WH_ARG_COUNT(float, int, double, bool);
	//OriginHelper::Debug_ScreenMessage(FString::FormatAsNumber(i));
	//OriginHelper::Debug_ScreenMessage(FString::FormatAsNumber(j));
	//OriginHelper::Debug_ScreenMessage(FString::FormatAsNumber(ArgCount));

	//OriginHelper::Debug_ScreenMessage(FString::SanitizeFloat(PlatformData.Speed.Plane_Speed));
	//OriginHelper::Debug_ScreenMessage(FString::FormatAsNumber(a + b));

	//OriginHelper::Debug_ScreenMessage(FString::FormatAsNumber(sizeof(str)), 10);

	//OriginHelper::Debug_ScreenMessage(FString::FormatAsNumber(sizeof(ABaseActor)-sizeof(APawn)),10);
	/*int32* a = (int32*)&this->a1;
	OriginHelper::Debug_ScreenMessage(FString::Printf(TEXT("%p"), a),5);
	OriginHelper::Debug_ScreenMessage(FString::Printf(TEXT("%p"), ++a),5);*/

	/*int64* StartPoint = &this->DefineStart;
	OriginHelper::Debug_ScreenMessage(FString::Printf(TEXT("%p"), StartPoint), 5);
	OriginHelper::Debug_ScreenMessage(FString::Printf(TEXT("%p"), &this->WH_FUN_STR), 5);
	OriginHelper::Debug_ScreenMessage(MoveTemp(*(FString*)(++StartPoint)),5);*/

	WH_FUN_DEFINE_IMPLEMENT();

	//BindFunctionPtr* Temp = GlobalBindFunctions.Find(FName(TEXT("SendID")));
	//(this->**GlobalBindFunctions.Find(FName(TEXT("SendID"))))(this);
	
	BindFunctionPtr ab = &ABaseActor::BindSendID;
	//OriginHelper::Debug_ScreenMessage(FString::Printf(TEXT("Function Pointer Width: %d"),sizeof(ab)),10);
	OriginHelper::Debug_ScreenMessage(FString::Printf(TEXT("Bind Function: %p"), &SendPosInfoBindPtr),10);

	OriginHelper::Debug_ScreenMessage(FString::Printf(TEXT("DelegateRemove Fun: %p"), &SendPosInfoRemoveDelegatePtr),10);
	OriginHelper::Debug_ScreenMessage(FString::Printf(TEXT("%p"), &SendIDBindPtr),10);

	OriginHelper::Debug_ScreenMessage(FString::FormatAsNumber(sizeof(BindFunctionPtr)),10);
	
	/*OriginHelper::Debug_ScreenMessage(FString::Printf(TEXT("%p"), &SendPosInfo_STR), 20);
	OriginHelper::Debug_ScreenMessage(FString::Printf(TEXT("%p"), &SendID_STR), 20);
	OriginHelper::Debug_ScreenMessage(FString::FormatAsNumber(sizeof(FSendIDDelegate)), 5);
	OriginHelper::Debug_ScreenMessage(FString::FormatAsNumber(sizeof(FSendPosInfoDelegate)), 5);*/
	
	/*UEnum* a = FindObject<UEnum>(ANY_PACKAGE, TEXT("EFunctionName"));
	TArray<TPair<FName, int64>> EnumElems;
	EnumElems.Add(TPair<FName, int64>(TEXT("WH_FUN"), 0));
	EnumElems.Add(TPair<FName, int64>(TEXT("WH_FUN_1"), 1));
	a->SetEnums(EnumElems, UEnum::ECppForm::Namespaced, false);*/
	
	//OriginHelper::Debug_ScreenMessage(a->GetNameByIndex(0).ToString(), 5);
	//a->SetEnums()
	//UScriptStruct*  b;
	
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
	MoveForwardImpl(Val);
}

void ABaseActor::MoveRight(float Val)
{
	MoveRightImpl(Val);
}

void ABaseActor::MoveForwardImpl(float Val)
{
	AddMovementInput(GetControlRotation().Vector(), Val);
}

void ABaseActor::MoveRightImpl(float Val)
{
	FRotator ControlRot = GetControlRotation();
	AddMovementInput(FRotationMatrix(ControlRot).GetUnitAxis(EAxis::Y), Val);
}

void ABaseActor::SetPlatformData(FName InID, ESQBTeam::Type InTeam)
{
	PlatformData->ID = InID;
	PlatformData->OwnerTeam = InTeam;
}

void ABaseActor::UpdatePlatformData()
{

}
