// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * ��Ŀͨ�÷�����
 */
class SCENEQUICKBUILD_API OriginHelper
{
public:
	static void Init(const FString& RelativePath);

	static void Debug_ScreenMessage(FString&& InString, float ShowTime = 1.f, FColor FontColor = FColor::Blue);

	static void Debug_LogMessage(FString&& InString);

	/* ���ļ�������Ϣ���Ǽ��ص��ַ�����
	 * @Param RelativePath ����Ϸ��Դ�ļ����е�λ�ã��������Դ�ļ��У�
	 * @Param FileName     �����ļ���
	 * @Param OutInfo      ��ȡ�������Ϣ
	 */
	static bool LoadInfoFromFile(const FString& RelativePath, const FString& FileName, FString& OutInfo);

	static void GetNumberFromJson(const FString& FileName, const FString& Key, float& OutNumber);

private:
	static FString PlaneConfigFileName;

	static FString RelativePath;
};
