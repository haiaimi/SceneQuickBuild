// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SceneQuickBuildType.h"
#include "BaseActor.generated.h"

/**
  * 场景中所有模块的基类，包括基本的控制模式，及模块的一些通用属性
  */
UCLASS()
class SCENEQUICKBUILD_API ABaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;	

	/**切换通信方式*/
	void SetCommunicateType(EOutsideCommunicate::Type InType);

	/**更新通信模式，在切换模式后通常还需要执行切换通信模式后的操作**/
	virtual void UpdateCommunicateType() {};

public:
	/**外部通信模式*/
	EOutsideCommunicate::Type CommunicateType;

private:
	/**该模块所在平台，该成员可以为空*/
	ABaseActor * OwnerPltform;
};
