// Fill out your copyright notice in the Description page of Project Settings.


#include "SocketHandler.h"


SocketHandler::SocketHandler(const FString& Name, const FString& TheIP, const int32 ThePort, const int32 ReceiveBufferSize, AAIServer* OwnerOfSocket)
{
	ListenSocket = CreateTCPConnectionListener(Name, TheIP, ThePort, ReceiveBufferSize);
	if (!ListenSocket)
	{
		UE_LOG(LogTemp, Warning, TEXT("Socket create failed"));
		return;
	}
	Owner = OwnerOfSocket;
	//Owner->GetWorldTimerManager().SetTimer(Handle, this,
	//	&SocketHandler::TCPConnectionListener, 0.01, true);
}


SocketHandler::~SocketHandler()
{
	ShutDownServer();
}


FSocket* SocketHandler::CreateTCPConnectionListener(const FString& YourChosenSocketName, const FString& TheIP, const int32 ThePort, const int32 ReceiveBufferSize)
{
	uint8 IP4Nums[4];


	//Create Socket
	FIPv4Endpoint Endpoint(FIPv4Address(IP4Nums[0], IP4Nums[1], IP4Nums[2], IP4Nums[3]), ThePort);
	FSocket* S = FTcpSocketBuilder(*YourChosenSocketName)
		.AsReusable()
		.BoundToEndpoint(Endpoint)
		.Listening(8);

	//Set Buffer Size
	int32 NewSize = ReceiveBufferSize;

	S->SetReceiveBufferSize(ReceiveBufferSize, NewSize);

	//Done!
	return S;
}



FString SocketHandler::StringFromBinaryArray(TArray<uint8> BinaryArray)
{
	BinaryArray.Add(0);
	return FString(UTF8_TO_TCHAR(reinterpret_cast<const char*>(BinaryArray.GetData())));
}


void SocketHandler::TCPConnectionListener()
{
	if (!ListenSocket) return;

	//Remote address
	TSharedRef<FInternetAddr> RemoteAddress = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	bool Pending;

	// handle incoming connections
	if (ListenSocket->HasPendingConnection(Pending) && Pending)
	{
		if (ConnectionSocket)
		{
			ConnectionSocket->Close();
			ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ConnectionSocket);
		}

		//new connection
		ConnectionSocket = ListenSocket->Accept(*RemoteAddress, TEXT("RamaTCP Received Socket Connection"));

		if (ConnectionSocket != NULL)
		{
			RemoteAddressForConnection = FIPv4Endpoint(RemoteAddress);
			//Delegate.BindLambda([this]() {Task(); });
			////Owner->GetWorldTimerManager().SetTimer(Handle, Delegate, 0.01, true);
			//Owner->GetWorldTimerManager().SetTimer(Handle, this,
			//	&SocketHandler::TCPSocketListener, 0.01, true);
		}
	}
}


void SocketHandler::TCPSocketListener()
{
	//Task();
}

void SocketHandler::ShutDownServer()
{
	UE_LOG(LogTemp, Warning, TEXT("Try to close connections (%s):"), *ListenSocket->GetDescription());
	if (ConnectionSocket)
	{
		ConnectionSocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ConnectionSocket);
		UE_LOG(LogTemp, Warning, TEXT("CLOSED CONNECTION SOCKET"));
	}

	if (ListenSocket) {
		ListenSocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ListenSocket);
		UE_LOG(LogTemp, Warning, TEXT("CLOSED LISTEN SOCKET"));
	}
}
