// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Common/TcpSocketBuilder.h"
#include <iostream>
#include "JsonHandler.h"
#include "RLEnviromentBase.h"
#include "AIServer.generated.h"


UCLASS()
class RL_MODULE_API AAIServer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAIServer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	FSocket* ListenSocket;
	FSocket* ConnectionListenSocket;

	FSocket* NotifySocket;
	FSocket* ConnectionNotifySocket;

	FIPv4Endpoint RemoteAddressForConnection;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void GymCall(FGymCommandStruct Data);

	FSocket* CreateTCPConnectionListener(const FString& YourChosenSocketName, const FString& TheIP, const int32 ThePort, const int32 ReceiveBufferSize);
	void TCPConnectionListener();
	void TCPSocketListener();


	FSocket* CreateTCPConnectionNotifier(const FString& YourChosenSocketName, const FString& TheIP, const int32 ThePort, const int32 ReceiveBufferSize);
	void TCPConnectionNotifier();
	void TCPSocketNotifier();

	FString StringFromBinaryArray(TArray<uint8> BinaryArray);

	UFUNCTION(BlueprintCallable, Category = Server)
	void ShutDownServer();

	void Step(TArray<float> Action);

	void Reset();

	TArray<float> GetState();

	float GetReward();

	bool IsDone();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Server Params")
		ARLEnviromentBase* Enviroment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Server Params")
		FString Host;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Server Params")
		int32 Port;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Server Params")
	bool bRunOnBeginPlay = true;
};
