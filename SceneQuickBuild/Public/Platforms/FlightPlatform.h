﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorldBase/BaseActor.h"
#include "FlightPlatform.generated.h"

static const FString FlightConfigName(TEXT("CommonPlane.json"));

/**
 * 飞行平台，目前就直接继承于BaseActor，后面会抽象出Platform中间层
 */
UCLASS()
class SCENEQUICKBUILD_API AFlightPlatform : public ABaseActor
{
	GENERATED_BODY()
	
public:
	AFlightPlatform();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;	

	virtual void UpdateCommunicateType()override;

	virtual void SetToTCP_UDPMode()override;

	virtual void SetToManualControlMode()override;

	virtual void SetToJsonMode()override;

	virtual void SetToXmlMode()override;

	//下面是飞行平台的移动方式，可以定制化移动方式
	virtual void Implementation_MoveForward(float Val);

	virtual void Implementation_MoveRight(float Val);

	UFUNCTION()
	void EventTest();

public:
	/**飞机网格模型*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent * PlaneMesh;

private:
	///该飞行平台的具体参数

	/**飞行平台的当前高度*/
	FVector FlyLocation;

	float FlySpeed;

	/**飞行平台的加速度*/
	float FlyAcceleration;
	
	/**飞行平台的各个模块，这里使用MultiMap是因为一个飞行可能有多个相同类型的模块如（导弹）*/
	TMultiMap<EPlatformModule::Type, ABaseActor*> FlightModules;
};
