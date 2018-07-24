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

/**平台各个模块枚举*/
UENUM(BlueprintType)
namespace EPlatformModule
{
	enum Type
	{
		EMissle_Air2Air,     //空对空到导弹
		EMissle_Air2Surfacfe,  //空对地导弹
		ERadar,      //雷达
	};
}