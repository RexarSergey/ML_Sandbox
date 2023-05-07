// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/TcpSocketBuilder.h"
#include <iostream>
#include <functional>
#include "JsonHandler.h"
#include "AIServer.h"
/**
 *
 */
//template<class T>
class RL_MODULE_API SocketHandler
{
public:

	SocketHandler(const FString& Name, const FString& TheIP, const int32 ThePort, const int32 ReceiveBufferSize, AAIServer* Owner);
	~SocketHandler();

protected:

	FTimerHandle Handle;
	FTimerDelegate Delegate;
	FSocket* ListenSocket;
	FSocket* ConnectionSocket;
	FIPv4Endpoint RemoteAddressForConnection;

public:

	FSocket* CreateTCPConnectionListener(const FString& YourChosenSocketName, const FString& TheIP, const int32 ThePort, const int32 ReceiveBufferSize);

	FString StringFromBinaryArray(TArray<uint8> BinaryArray);

	void TCPConnectionListener();

	virtual void TCPSocketListener();

	void ShutDownServer();

public:
	std::function<void()> Task;
	AAIServer* Owner;
};


//class RL_MODULE_API ListenHandler {
//public:
//	void TCPSocketListener();
//};