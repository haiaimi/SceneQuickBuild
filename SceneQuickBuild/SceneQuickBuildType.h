// Fill out your copyright notice in the Description page of Project Settings.

#include "CoreMinimal.h"
#include "SceneQuickBuildType.generated.h"

#pragma once

/**
* 该项目中常用的类型，枚举，结构等等
*/


/**基础组件的通信模式*/
UENUM(BlueprintType)
namespace EOutsideCommunicate
{
	enum Type
	{
		EUDP_TCP,      //通过TCP/UDP来进行通信
		EManualControl,      //手动模式
		ELoadConfigFile_Json,   //通过读取配置文件
		ELoadConfigFile_Xml,
	};
}

/**各个不同平台的枚举*/
namespace EPlatformCategory
{
	enum Type
	{
		EBaseModule,      //基础模块
		EFlight,          //飞行平台
		ETank,            //陆地坦克
	};
}

/**平台各个模块枚举*/
UENUM(BlueprintType)
namespace EPlatformModule
{
	enum Type
	{
		EMissle_Air2Air,     //空对空到导弹
		EMissle_Air2Surface,  //空对地导弹
		ERadar,      //雷达
	};
}

/**本方与敌方*/
UENUM(BlueprintType)
namespace ESQBTeam
{
	enum Type
	{
		UnKnow,
		EPlayer,   //玩家本方
		EEnemy,     //敌方
	};
}

/**平台的信息*/
USTRUCT(BlueprintType)
struct FPlatformData
{
	GENERATED_USTRUCT_BODY()

	/**所属队伍*/
	ESQBTeam::Type OwnerTeam;

	/**平台类型*/
	EPlatformCategory::Type PlatformType;
};