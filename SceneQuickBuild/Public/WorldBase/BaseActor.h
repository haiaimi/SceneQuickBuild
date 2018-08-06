﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SceneQuickBuildType.h"
#include "GameFramework/Pawn.h"
#include "BaseActor.generated.h"

/**
  * 场景中所有模块的基类，包括基本的控制模式，及模块的一些通用属性
  */
UCLASS()
class SCENEQUICKBUILD_API ABaseActor : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;	

	virtual void BeginDestroy()override;

	/**切换通信方式*/
	void SetCommunicateType(EOutsideCommunicate::Type InType);

	void SetMaxSpeed(float InSpeed);

	/**更新通信模式，在切换模式后通常还需要执行切换通信模式后的操作**/
	virtual void UpdateCommunicateType() {};

	/**TCP/UDP通信方式，设置对应的Receiver和Sender*/
	virtual void SetToTCP_UDPMode() {};

	/**手动控制模式*/
	virtual void SetToManualControlMode() {};

	/**读取Json外部文件模式*/
	virtual void SetToJsonMode() {};

	/**读取Xml外部文件模式*/
	virtual void SetToXmlMode() {};

	//下面都是基本的移动
	virtual void MoveForward(float Val);

	virtual void MoveRight(float Val);

	//移动方法内部具体实现，可以在派生类中重写
	virtual void Implementation_MoveForward(float Val);

	virtual void Implementation_MoveRight(float Val);

	/**获取平台信息*/
	struct FPlatformData GetPlatformData() { return PlatformData; };

	/**设置平台信息*/
	void SetPlatformData(FName InID, ESQBTeam::Type InTeam);

	FPlatformData& GetBaseData() { return PlatformData; }

	/**宏测试*/
	WH_DEFINE_FUN(WH_FUN, void, float, speed, int, num);
	FWH_FUNDelegate A;

	WH_DEFINE_FUN(WH_FUN_1, void, FVector, speed, int32, num, bool, visible);
	FWH_FUN_1Delegate B;

	UPROPERTY()
	static FString FunName;
	/*void PublishMessage();

	void SubscribeMessage();*/


	GET_SPECIFIED_PLATFORM_DATA(PlatformData.ID, TArray<FName>, AllOtherName, this);

	//BUILD_COMMUNICATE(a, a, FTest, Test, float, int);
	
public:
	/**外部通信模式*/
	EOutsideCommunicate::Type CommunicateType;

	class USceneComponent* BaseScene;

	class UPawnMovementComponent* ModuleMovement;

	class UCameraComponent* ViewCamera;

	/** 平台信息，包含平台的一些基础信息*/
	struct FPlatformData PlatformData;

protected:
	/**平台类型*/
	EPlatformCategory::Type PlatformType;

private:
	/**该模块所在平台，该成员可以为空*/
	class ABaseActor * OwnerPltform;

	/**信息发布的代理*/
	FMessagePublish MessagePublicDel;
};
