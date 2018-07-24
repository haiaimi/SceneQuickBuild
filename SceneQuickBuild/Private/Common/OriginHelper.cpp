// Fill out your copyright notice in the Description page of Project Settings.

#include "Common/OriginHelper.h"
#include "Engine/Engine.h"
#include "SceneQuickBuild.h"
#include "Paths.h"
#include "FileHelper.h"
#include "JsonReader.h"

FString OriginHelper::PlaneConfigFileName = FString(TEXT("CommonPlane.json"));    //初始化文件名称
FString OriginHelper::RelativePath = FString(TEXT("ConfigRes/FlightPlatform"));

void OriginHelper::Init(const FString& InRelativePath)
{
	RelativePath = InRelativePath;
}

void OriginHelper::Debug_ScreenMessage(FString&& InString, float ShowTime, FColor FontColor)
{
	GEngine->AddOnScreenDebugMessage(-1, ShowTime, FontColor, InString);
}

void OriginHelper::Debug_LogMessage(FString&& InString)
{
	UE_LOG(LogOrigin, Log, TEXT("%s"), *InString)
}

bool OriginHelper::LoadInfoFromFile(const FString& RelativePath, const FString& FileName, FString& OutInfo)
{
	if (FileName.IsEmpty())return false;

	FString AbsolutePath = FPaths::ProjectContentDir() + RelativePath + FileName;
	if (FPaths::FileExists(AbsolutePath))
	{
		if (FFileHelper::LoadFileToString(OutInfo, *AbsolutePath))
			return true;      //加载成功
		else
			Debug_ScreenMessage(TEXT("未找到文件"), 5.f);
	}

	return false;
}

void OriginHelper::GetNumberFromJson(const FString& FileName, const FString& Key, float& OutNumber)
{
	FString JsonContent;
	if (LoadInfoFromFile(RelativePath, FileName, JsonContent))
	{
		TSharedRef< TJsonReader<FJsonValue> > JsonParser;  //json解析
		TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonContent);       //创建Json读取实例类

		if(FJsonSerializer::Deserialize())
	}
}
