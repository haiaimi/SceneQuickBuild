﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorldBase/BaseActor.h"
#include "FlightPlatform.generated.h"

static const FString FlightConfigName(TEXT("CommonPlane.json"));
struct FBaseActorData;

/**
 * 飞行平台，目前就直接继承于BaseActor，后面会抽象出Platform中间层
 */
UCLASS()
class SCENEQUICKBUILD_API AFlightPlatform : public ABaseActor
{
	GENERATED_BODY()
	
public:
	AFlightPlatform(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)override;

public:	
	virtual void Tick(float DeltaTime) override;	

	virtual void BeginDestroy()override;

	virtual void UpdateCommunicateType()override;

	virtual void SetToTCP_UDPMode()override;

	virtual void SetToManualControlMode()override;

	virtual void SetToJsonMode()override;

	virtual void SetToXmlMode()override;

	//下面是飞行平台的移动方式，可以定制化移动方式
	virtual void MoveForwardImpl(float Val);

	virtual void MoveRightImpl(float val);

	/**飞机朝上飞行*/
	void MoveUp(float Val);

	virtual void UpdatePlatformData()override;

	virtual void Test()
	{
		Super::Test();

		OriginHelper::Debug_ScreenMessage(TEXT("Child"), 10);
	}

	UFUNCTION()
	int32 EventTest(float Speed, int32 Num);

	float GetFlySpeed() { return FlySpeed; };

private:
	/**获取飞行平台的向上的向量*/
	FVector GetUpVector();

	/**获取飞机恢复中心转向的角度*/
	float GetToCenterSubAngle();

	/**描述飞机起飞的过程*/
	void TakeOff(float DeltaTime);
public:
	/**飞机网格模型*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent * PlaneMesh;

private:
	/**起飞使用的时间*/
	float TakeOffAngle;
	///该飞行平台的具体参数

	/**飞行平台的当前高度*/
	FVector FlyLocation;

	float FlySpeed;

	/**飞行平台的加速度*/
	float FlyAcceleration;

	/**当前飞机是否在空中*/
	uint8 bInAir : 1;

    float CurOffsetAngle_Right = 0.f;  

	float CurOffsetAngle_Up = 0.f;

	/**飞机碰撞体*/
	class UBoxComponent* PlaneBox;

	FFlightPlatformData* ExpandPlatformData;
	
	/**飞行平台的各个模块，这里使用MultiMap是因为一个飞行可能有多个相同类型的模块如（导弹）*/
	TMultiMap<EPlatformModule::Type, ABaseActor*> FlightModules;
};
