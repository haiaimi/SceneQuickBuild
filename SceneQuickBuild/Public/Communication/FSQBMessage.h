// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * ��Ϣ��
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
	/**��Ϣ����*/
	T* MessageContent;


};

/**
 * ��Ϣ��
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
	/**��Ϣ�б�������е���Ϣ*/
	TArray<FSQBMessage<T>*> MessageList;
};