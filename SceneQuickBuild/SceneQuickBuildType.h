// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "Gameplay/SQBGameInstance.h"
#include "OriginHelper.h"
#include "SceneQuickBuildType.generated.h"

/**
* 该项目中常用的宏，类型，枚举，结构等等
*/

//信息发布多播代理
DECLARE_MULTICAST_DELEGATE_OneParam(FMessagePublish, FString&);

#define EXPAND(x) x
#define WH_CONCAT_(l,r) l##r
#define WH_CONCAT(l,r) WH_CONCAT_(l,r) 

/**
* 下面的宏是用来计算宏可变参数列表的参数数量，这里最大计算6个，如果有需求可以继续添加
* 这里 _VA_ARGS__前面一定要加##，否则参数为空时会报错
*/
#define WH_INTERNAL_ARG_COUNT( \
	_0, _1, _2, _3, _4, _5, _6, N, ...) N

#define WH_ARG_COUNT(...) EXPAND(WH_INTERNAL_ARG_COUNT(0, ##__VA_ARGS__, \
	6, 5, 4, 3, 2, 1, 0))

/*计算可变参数列表的一般数目*/
#define WH_ARG_COUNT_HALF(...) EXPAND(WH_INTERNAL_ARG_COUNT(0, ##__VA_ARGS__,\
	3, 2.5, 2, 1.5, 1, 0.5, 0))

#define WH_DOARG0(o)
#define WH_DOARG1(v_1,v_2,...) v_1  v_2
#define WH_DOARG2(v_1,v_2,...) WH_DOARG1(v_1,v_2) , EXPAND(WH_DOARG1(##__VA_ARGS__))
#define WH_DOARG3(v_1,v_2,...) WH_DOARG1(v_1,v_2) , EXPAND(WH_DOARG2(##__VA_ARGS__))
#define WH_DOARG4(v_1,v_2,...) WH_DOARG1(v_1,v_2) , EXPAND(WH_DOARG3(##__VA_ARGS__))

#define WH_FOREACH_(...) \
        EXPAND(WH_CONCAT(WH_DOARG,WH_ARG_COUNT_HALF(__VA_ARGS__))(##__VA_ARGS__))
#define WH_FOREACH(...) \
        EXPAND(WH_FOREACH_(##__VA_ARGS__))

#define FUN_ARGS(p,n) p##n

#define WH_DEF_FUN(funName,retType,...)\
retType funName(\
EXPAND(WH_FOREACH(##__VA_ARGS__))\
)

/**多参数列表测试代码*/
#define WH_TEST1__(v1,v2,...) \
int32 j = WH_CONCAT(v1,v2);

#define WH_TEST1_(v1,v2,...) \
int32 i = WH_CONCAT(v1,v2); \
EXPAND(WH_TEST1__(##__VA_ARGS__))

#define WH_TEST1(...) EXPAND(WH_TEST1_(##__VA_ARGS__))

#define GET_SPECIFIED_PLATFORM_DATA(PlatformID, DataType, DataName, ActorRef) \
DataType GetData_##DataName()     \
{     \
	DataType Temp;   \
	if(GetWorld())  \
	{  \
		if (USQBGameInstance* GameInstance = Cast<USQBGameInstance>(GetWorld()->GetGameInstance()))  \
		{            \
			Temp = GameInstance->GetData_##DataName(PlatformID, ActorRef); \
		}           \
	}    \
	return Temp;     \
}


//#define BUILD_COMMUNICATE(PublishActor, SubscribeActor, DelegateName, DelegateInstance, ...)  \
//FUNC_DECLARE_DELEGATE(DelegateName, ...)  \
//DelegateName DelegateInstance;   \
//template<typename Type1> \
//void Communicate_##DelegateName(Type1 Val1)    \
//{ \
//   \ 
//}


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

	/**平台ID，每个平台实例都有独立的ID号*/
	FName ID;

	/**所属队伍*/
	ESQBTeam::Type OwnerTeam;

	/**平台类型*/
	EPlatformCategory::Type PlatformType;

	/**平台所在位置*/
	FVector PlatformPos;

	union PlatformData_Speed
	{
		float Plane_Speed;
		float Tank_Speed;
		float Ship_Speed;
	};

	PlatformData_Speed Speed;
};

/**具体的飞行平台*/
USTRUCT(BlueprintType)
struct FFlightData :public FPlatformData
{
	GENERATED_USTRUCT_BODY();

	/**飞行速度*/
	float FlySpeed;

	/**加速度*/
	float FlyAcceleration;


	/***/
};