// Fill out your copyright notice in the Description page of Project Settings.


#include "AIServer.h"
#include <Interfaces/IPv4/IPv4Address.h>
#include "Interfaces/IPv4/IPv4Endpoint.h"
#include "JsonHandler.h"
#include "RLEnums.h"
#include "Containers/StringConv.h"

// Sets default values
AAIServer::AAIServer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


// Called when the game starts or when spawned
void AAIServer::BeginPlay()
{
	Super::BeginPlay();

	ListenSocket = CreateTCPConnectionListener(FString("Listen"), Host, Port, 65507u);
	if (!ListenSocket)
	{
		UE_LOG(LogTemp, Warning, TEXT("Socket create failed"));
		return;
	}
	FTimerHandle Handle1;
	GetWorldTimerManager().SetTimer(Handle1, this,
		&AAIServer::TCPConnectionListener, 0.01, true);

	NotifySocket = CreateTCPConnectionNotifier(FString("Notify"), Host, Port - 1, 65507u);
	if (!NotifySocket)
	{
		UE_LOG(LogTemp, Warning, TEXT("Socket create failed"));
		return;
	}

	FTimerHandle Handle2;
	GetWorldTimerManager().SetTimer(Handle2, this,
		&AAIServer::TCPConnectionNotifier, 0.01, true);

}


// Called every frame
void AAIServer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


FSocket* AAIServer::CreateTCPConnectionListener(const FString& YourChosenSocketName, const FString& TheIP, const int32 ThePort, const int32 ReceiveBufferSize)
{
	//uint8 IP4Nums[4];

	FIPv4Address IpAddr;
	FIPv4Address::Parse(TheIP, IpAddr);

	//Create Socket
	FIPv4Endpoint Endpoint(IpAddr, ThePort);
	FSocket* S = FTcpSocketBuilder(*YourChosenSocketName)
		.AsReusable()
		.BoundToEndpoint(Endpoint)
		.Listening(8);

	if (S == nullptr) {
		return S;
	}
	//Set Buffer Size
	int32 NewSize = ReceiveBufferSize;

	S->SetReceiveBufferSize(ReceiveBufferSize, NewSize);

	//Done!
	return S;
}

FSocket* AAIServer::CreateTCPConnectionNotifier(const FString& YourChosenSocketName, const FString& TheIP, const int32 ThePort, const int32 ReceiveBufferSize)
{
	FIPv4Address IpAddr;
	FIPv4Address::Parse(TheIP, IpAddr);

	//Create Socket
	FIPv4Endpoint Endpoint(IpAddr, ThePort);
	FSocket* S = FTcpSocketBuilder(*YourChosenSocketName)
		.AsReusable()
		.BoundToEndpoint(Endpoint)
		.Listening(8);

	if (S == nullptr) {
		return S;
	}
	//Set Buffer Size
	int32 NewSize = ReceiveBufferSize;

	S->SetReceiveBufferSize(ReceiveBufferSize, NewSize);

	//Done!
	return S;
}

void AAIServer::TCPConnectionListener()
{
	if (!ListenSocket) return;

	//Remote address
	TSharedRef<FInternetAddr> RemoteAddress = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	bool Pending;

	// handle incoming connections
	if (ListenSocket->HasPendingConnection(Pending) && Pending)
	{
		if (ConnectionListenSocket)
		{
			ConnectionListenSocket->Close();
			ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ConnectionListenSocket);
		}

		//new connection
		ConnectionListenSocket = ListenSocket->Accept(*RemoteAddress, TEXT("RamaTCP Received Socket Connection"));

		if (ConnectionListenSocket != NULL)
		{
			RemoteAddressForConnection = FIPv4Endpoint(RemoteAddress);

			FTimerHandle Handle;
			GetWorldTimerManager().SetTimer(Handle, this,
				&AAIServer::TCPSocketListener, 0.01, true);
		}
	}
}

void AAIServer::TCPConnectionNotifier()
{
	if (!NotifySocket) return;

	//Remote address
	TSharedRef<FInternetAddr> RemoteAddress = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	bool Pending;

	// handle incoming connections
	if (NotifySocket->HasPendingConnection(Pending) && Pending)
	{
		if (ConnectionNotifySocket)
		{
			ConnectionNotifySocket->Close();
			ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ConnectionNotifySocket);
		}

		//new connection
		ConnectionNotifySocket = NotifySocket->Accept(*RemoteAddress, TEXT("RamaTCP Received Socket Connection"));

		//if (ConnectionNotifySocket != NULL)
		//{
		//	RemoteAddressForConnection = FIPv4Endpoint(RemoteAddress);

		//	GetWorldTimerManager().SetTimer(Handle, this,
		//		&AAIServer::TCPConnectionNotifier, 0.01, true);
		//}
	}
}


FString AAIServer::StringFromBinaryArray(TArray<uint8> BinaryArray)
{
	BinaryArray.Add(0);
	return FString(UTF8_TO_TCHAR(reinterpret_cast<const char*>(BinaryArray.GetData())));
}


void AAIServer::TCPSocketListener()
{
	if (!ConnectionListenSocket) return;
	TArray<uint8> Data;
	uint32 Size;
	int32 BytesRead = 0;
	while (ConnectionListenSocket->HasPendingData(Size)) {
		uint8 elem;
		Data.Init(elem, FMath::Min(Size, 65507u));

		ConnectionListenSocket->Recv(Data.GetData(), Size, BytesRead);

	}
	if (BytesRead > 0) {
		FString RawStringData = StringFromBinaryArray(Data);
		FString StringData = RawStringData;

		UE_LOG(LogTemp, Warning, TEXT("READ Bytes: %d; String: %s"), BytesRead, *StringData);
		bool bS;
		FPythonCommandStruct s = JsonHandler::ReadFGymCommandStruct(StringFromBinaryArray(Data), bS);
		PythonCall(s);

	}
}

void AAIServer::TCPSocketNotifier()
{
	if (!ConnectionListenSocket) return;

	FString SendString = "1";
	int32 BytesSent;
	FTCHARToUTF8 Converted(*SendString);
	ConnectionNotifySocket->Send((uint8*)Converted.Get(), Converted.Length(), BytesSent);
	UE_LOG(LogTemp, Warning, TEXT("Notify!"));
}

void AAIServer::PythonCall(FPythonCommandStruct Data)
{
	TEnumAsByte<ECommandEnum> Command(Data.id);

	switch (Command.GetValue())
	{
	case ECommandEnum::Step:
		Step(Data.action);
		break;
	case ECommandEnum::Reset:
		Reset();
		break;
	case ECommandEnum::State:
		GetState();
		break;
	case ECommandEnum::Reward:
		GetReward();
		break;
	case ECommandEnum::IsDone:
		IsDone();
		break;
	case ECommandEnum::GetDQNLearning:
		GetDQNLearning();
		break;
	default:
		break;
	}


}


void AAIServer::ShutDownServer() {

	if (ConnectionListenSocket)
	{
		ConnectionListenSocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ConnectionListenSocket);
		UE_LOG(LogTemp, Warning, TEXT("CLOSED CONNECTION LISTEN SOCKET"));
	}

	if (ListenSocket) {
		ListenSocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ListenSocket);
		UE_LOG(LogTemp, Warning, TEXT("CLOSED LISTEN SOCKET"));

	}

	if (ConnectionNotifySocket)
	{
		ConnectionNotifySocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ConnectionNotifySocket);
		UE_LOG(LogTemp, Warning, TEXT("CLOSED CONNECTION NOTIFY SOCKET"));
	}

	if (NotifySocket) {
		NotifySocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(NotifySocket);
		UE_LOG(LogTemp, Warning, TEXT("CLOSED NOTIFY SOCKET"));

	}

	if (ProcHandle.IsValid()) {
		ProcHandle.Reset();
	}

	Destroy();
}

void AAIServer::RunFit()
{
	if (PythonPath == "") {
		PythonPath = FPaths::ProjectPluginsDir() + "RL_Module\\Content\\venv\\Scripts\\python.exe";
	}
	FString savePath;
	if (Enviroment->SaveDirectory == "") {
		savePath = "saved\\" + Enviroment->SaveFileName;
	}
	else {
		savePath = Enviroment->SaveDirectory + "\\" + Enviroment->SaveFileName;
	}

	FString loadPath;
	if (Enviroment->LoadDirectory == "") {
		loadPath = "saved\\" + Enviroment->SaveFileName;
	}
	else {
		loadPath = Enviroment->LoadDirectory + "\\" + Enviroment->SaveFileName;
	}

	if (OptionalWorkingDirectory == "") {
		OptionalWorkingDirectory = FPaths::ProjectPluginsDir() + "RL_Module\\Content\\python_code\\";
	}

	if (PythonProgramFitPath == "") {
		PythonProgramFitPath = "release\\run_fit.py";
	}


	FString params = PythonProgramFitPath + " " + Host + " " + FString::FromInt(Port)
		+ " " + savePath + " " + loadPath;
	ProcHandle = FPlatformProcess::CreateProc(*PythonPath, *params, true, false, false, nullptr, 1, *OptionalWorkingDirectory, nullptr);
}

void AAIServer::RunAI()
{
	if (PythonPath == "") {
		PythonPath = FPaths::ProjectPluginsDir() + "RL_Module\\Content\\venv\\Scripts\\python.exe";
	}
	FString savePath;
	if (Enviroment->SaveDirectory == "") {
		savePath = "saved\\" + Enviroment->SaveFileName;
	}
	else {
		savePath = Enviroment->SaveDirectory + "\\" + Enviroment->SaveFileName;
	}

	FString loadPath;
	if (Enviroment->LoadDirectory == "") {
		loadPath = "saved\\" + Enviroment->SaveFileName;
	}
	else {
		loadPath = Enviroment->LoadDirectory + "\\" + Enviroment->SaveFileName;
	}

	if (OptionalWorkingDirectory == "") {
		OptionalWorkingDirectory = FPaths::ProjectPluginsDir() + "RL_Module\\Content\\python_code\\";
	}

	if (PythonProgramRunPath == "") {
		PythonProgramRunPath = "release\\run_ai.py";

	}


	FString params = PythonProgramRunPath + " " + Host + " " + FString::FromInt(Port)
		+ " " + savePath + " " + loadPath;
	ProcHandle = FPlatformProcess::CreateProc(*PythonPath, *params, true, false, false, nullptr, 1, *OptionalWorkingDirectory, nullptr);
}

void AAIServer::Step(TArray<float> Action)
{
	Enviroment->Action = Action;
	Enviroment->Step();
	TCPSocketNotifier();
}

void AAIServer::Reset()
{
	Enviroment->Reset();
	TCPSocketNotifier();
}

TArray<float> AAIServer::GetState()
{
	Enviroment->GetState();

	FGymStateStruct SendStruct;
	FString SendString;
	int32 BytesSent;
	bool b;

	SendStruct.State = Enviroment->GetState();
	SendString = JsonHandler::CreateFGymStateStruct(SendStruct, b);
	FTCHARToUTF8 Converted(*SendString);
	ConnectionNotifySocket->Send((uint8*)Converted.Get(), Converted.Length(), BytesSent);
	UE_LOG(LogTemp, Warning, TEXT("Bytes Sent: %d; Sent String: %s"), Converted.Length(), *SendString);
	return SendStruct.State;
}

float AAIServer::GetReward()
{
	FGymStateStruct SendStruct;
	FString SendString;
	int32 BytesSent;
	bool b;

	SendStruct.Reward = Enviroment->GetReward();
	SendString = JsonHandler::CreateFGymStateStruct(SendStruct, b);
	FTCHARToUTF8 Converted(*SendString);
	ConnectionNotifySocket->Send((uint8*)Converted.Get(), Converted.Length(), BytesSent);
	UE_LOG(LogTemp, Warning, TEXT("Bytes Sent: %d; Sent String: %s"), Converted.Length(), *SendString);
	return SendStruct.Reward;
}

bool AAIServer::IsDone()
{
	FGymStateStruct SendStruct;
	FString SendString;
	int32 BytesSent;
	bool b;

	SendStruct.IsDone = Enviroment->IsDone();
	SendString = JsonHandler::CreateFGymStateStruct(SendStruct, b);
	FTCHARToUTF8 Converted(*SendString);
	ConnectionNotifySocket->Send((uint8*)Converted.Get(), Converted.Length(), BytesSent);
	UE_LOG(LogTemp, Warning, TEXT("Bytes Sent: %d; Sent String: %s"), Converted.Length(), *SendString);
	return SendStruct.IsDone;
}

void AAIServer::GetDQNLearning()
{
	UE_LOG(LogTemp, Warning, TEXT("HERE"));
	FDQNLearningStruct SendStruct;
	FString SendString;
	int32 BytesSent;
	bool b;
	SendStruct = Enviroment->DQNStruct;
	//SendStruct.Network = Enviroment->NetworkNeurones;
	//SendStruct.Activations = Enviroment->NetworkActivations;
	SendString = JsonHandler::CreateFDQNLearningStruct(SendStruct, b);
	FTCHARToUTF8 Converted(*SendString);
	ConnectionNotifySocket->Send((uint8*)Converted.Get(), Converted.Length(), BytesSent);
	UE_LOG(LogTemp, Warning, TEXT("Bytes Sent: %d; Sent String: %s"), Converted.Length(), *SendString);
}

