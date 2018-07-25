// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#define  TypeToChar(T) #T
#define EnumsFromJson(FileName,Key,EnumType,Index,OutEnums) OriginHelper::GetEnumsFromJson(FileName,Key,TEXT(TypeToChar(EnumType)),Index,OutEnums);
/**
 * 项目通用方法库
 */
class SCENEQUICKBUILD_API OriginHelper
{
public:
	static void Init(const FString& RelativePath);

	static void Debug_ScreenMessage(FString&& InString, float ShowTime = 1.f, FColor FontColor = FColor::Blue);

	static void Debug_LogMessage(FString&& InString);
	
	///向Json中写入（序列化相关）Begin

	/** 向文件写入Json数据
	  * @Param RelativePath 在游戏资源文件夹中的位置（相对于资源文件夹）
	  * @Param FileName     配置文件名 
	  * @Param JsonData     Json文件的字符串数据
	  */
	static bool WriteJsonToFile(const FString& RelativePath, const FString& FileName, const FString& JsonData);

	static void SerializeNumber();

	///向Json中写入（序列化相关）End

	///Json文件读取相关(反序列化) Begin

	/* 从文件加载信息，是加载到字符串里
	 * @Param RelativePath 在游戏资源文件夹中的位置（相对于资源文件夹）
	 * @Param FileName     配置文件名
	 * @Param OutInfo      读取输出的信息
	 */
	static bool LoadStringFromFile(const FString& RelativePath, const FString& FileName, FString& OutInfo);

	/** 准备Json读取，就是事先从文件读取文件，并构建Json对象用以读取文件,所以尽量一个一个文件的读，否则会浪费性能
	  * @Param FileName Json文件名称
	  */
	static void PrepareJson(const FString& FileName);

	/** 获取Json中对应的具体类型的具体数据
	  * @Param Index 读取Json中数据对象的序号
	  */
	static void GetNumberFromJson(const FString& FileName, const FString& Key, const int32 Index, float& OutNumber);

	/** 获取向量*/
	static void GetVectorFromJson(const FString& FileName, const FString& Key, const int32 Index, FVector& OutVector);

	/** 获取枚举，可以为多个*/
	static void GetEnumsFromJson(const FString& FileName, const FString& Key, const FString& EnumName, const int32 Index, TArray<int32>& OutEnums);

	/** 删除刚刚读取的Json相关文件,以便下次读取新的Json文件，就是读取下一个文件时必须执行该方法，不然会读取失败*/
	static void ResetJson();
	///Json文件读取相关（反序列化） End

private:
	/** 文件相对路径（相对于游戏文件夹）*/
	static FString RelativePath;
	/** 当前解析的文件*/
	static FString CurParseFile;
	/** 解析的结果*/
	static TArray<TSharedPtr<class FJsonValue>>  JsonParser;
};
