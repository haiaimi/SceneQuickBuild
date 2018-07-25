// Fill out your copyright notice in the Description page of Project Settings.

#include "Common/OriginHelper.h"
#include "Engine/Engine.h"
#include "SceneQuickBuild.h"
#include "Paths.h"
#include "FileHelper.h"
#include "JsonReader.h"

FString OriginHelper::CurParseFile = FString(TEXT("CommonPlane.json"));    //初始化文件名称
FString OriginHelper::RelativePath = FString(TEXT("ConfigRes/FlightPlatform"));
TArray<TSharedPtr<FJsonValue>> OriginHelper::JsonParser = {};

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

bool OriginHelper::WriteJsonToFile(const FString& RelativePath, const FString& FileName, const FString& JsonData)
{
	if (JsonData.IsEmpty())return false;

	if (!FileName.IsEmpty())
	{
		FString AbsolutePath = FPaths::ProjectContentDir() + RelativePath + "/" + FileName;
		if(FFileHelper::SaveStringToFile(JsonData,*AbsolutePath))
		{
			Debug_LogMessage(TEXT("文件保存成功"));
			return true;
		}
		else
		{
			Debug_LogMessage(TEXT("文件保存失败"));
			return false;
		}
	}
}

bool OriginHelper::LoadStringFromFile(const FString& RelativePath, const FString& FileName, FString& OutInfo)
{
	if (FileName.IsEmpty())return false;

	FString AbsolutePath = FPaths::ProjectContentDir() + RelativePath + "/" + FileName;
	if (FPaths::FileExists(AbsolutePath))
	{
		if (FFileHelper::LoadFileToString(OutInfo, *AbsolutePath))
			return true;      //加载成功
		else
			Debug_LogMessage(TEXT("未找到文件"));
	}

	return false;
}

void OriginHelper::PrepareJson(const FString& FileName)
{
	FString JsonContent;
	CurParseFile = FileName;
	if (LoadStringFromFile(RelativePath, FileName, JsonContent))
	{
		TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonContent);       //创建Json读取实例类

		if (FJsonSerializer::Deserialize(JsonReader, JsonParser))    //反序列化
			Debug_LogMessage(TEXT("读取成功"));
		else
			Debug_LogMessage(TEXT("读取失败"));
	}
}

void OriginHelper::GetNumberFromJson(const FString& FileName, const FString& Key, const int32 Index, float& OutNumber)
{
	//Debug_LogMessage(FString::FormatAsNumber(JsonParser.Num()));
	if (FileName.Equals(CurParseFile) && JsonParser.Num() > 0)
	{
		OutNumber = JsonParser[Index]->AsObject()->GetNumberField(Key);
	}
	else
		Debug_LogMessage(TEXT("请重新读取文件"));
}

void OriginHelper::GetVectorFromJson(const FString& FileName, const FString& Key, const int32 Index, FVector& OutVector)
{
	if (FileName.Equals(CurParseFile) && JsonParser.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> VectorAxisArray = JsonParser[Index]->AsObject()->GetArrayField(Key);

		if (VectorAxisArray.Num() == 3)   //向量必须要有三个分量
		{
			OutVector.X = VectorAxisArray[0]->AsNumber();
			OutVector.Y = VectorAxisArray[1]->AsNumber();
			OutVector.Z = VectorAxisArray[2]->AsNumber();
		}
		else
			Debug_LogMessage(TEXT("向量信息有误"));
	}
	else
		Debug_LogMessage(TEXT("请重新读取文件"));
}

void OriginHelper::GetEnumsFromJson(const FString& FileName, const FString& Key, const FString& EnumName, const int32 Index, TArray<int32>& OutEnums)
{
	OutEnums.Reset();
	if (FileName.Equals(CurParseFile) && JsonParser.Num() > 0)
	{
		UEnum* TargetEnum = FindObject<UEnum>(ANY_PACKAGE, *EnumName);
		//int32 i = TargetEnum->GetValueByNameString(TEXT(""))
		TArray<TSharedPtr<FJsonValue>> EnumsArray = JsonParser[Index]->AsObject()->GetArrayField(Key);
		if (TargetEnum)
		{
			for (auto& Iter : EnumsArray)
			{
				int32 IntEnum = TargetEnum->GetValueByNameString(Iter->AsString());
				Debug_LogMessage(Iter->AsString());
				if (IntEnum != INDEX_NONE)
					OutEnums.Add(IntEnum);
			}
		}
	}
	else
		Debug_LogMessage(TEXT("请重新读取文件"));
}

void OriginHelper::ResetJson()
{
	CurParseFile.Empty();
	JsonParser.Empty();
}
