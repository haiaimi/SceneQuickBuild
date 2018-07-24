// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 项目通用方法库
 */
class SCENEQUICKBUILD_API OriginHelper
{
public:
	static void Init(const FString& RelativePath);

	static void Debug_ScreenMessage(FString&& InString, float ShowTime = 1.f, FColor FontColor = FColor::Blue);

	static void Debug_LogMessage(FString&& InString);

	/* 从文件加载信息，是加载到字符串里
	 * @Param RelativePath 在游戏资源文件夹中的位置（相对于资源文件夹）
	 * @Param FileName     配置文件名
	 * @Param OutInfo      读取输出的信息
	 */
	static bool LoadInfoFromFile(const FString& RelativePath, const FString& FileName, FString& OutInfo);

	static void GetNumberFromJson(const FString& FileName, const FString& Key, float& OutNumber);

private:
	static FString PlaneConfigFileName;

	static FString RelativePath;
};
