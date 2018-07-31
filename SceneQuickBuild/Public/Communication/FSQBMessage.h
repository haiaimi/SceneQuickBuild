// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 消息类
 */
template<class T>
class FSQBMessage
{
public:
	FSQBMessage()
	{
	
	}

	~FSQBMessage()
	{

	}

private:
	/**信息内容*/
	T* MessageContent;


};

/**
 * 消息池
 */
template<class T>
class FSQBMessagePool
{
public:
	FSQBMessagePool()
	{

	}

	~FSQBMessagePool()
	{
		for (auto Iter : MessageList)
		{
			delete Iter;
		}
	}

private:
	/**消息列表，存放所有的消息*/
	TArray<FSQBMessage<T>*> MessageList;
};