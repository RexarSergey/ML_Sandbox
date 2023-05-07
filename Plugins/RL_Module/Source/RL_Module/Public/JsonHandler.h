// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JsonHandler.generated.h"


USTRUCT(BlueprintType)
struct RL_MODULE_API FGymCommandStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FGymCommandStruct Json")
	int32 id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FGymCommandStruct Json")
	TArray<float> action;

};

USTRUCT(BlueprintType)
struct RL_MODULE_API FGymStateStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FGymStateStruct Json")
		bool IsDone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FGymStateStruct Json")
		TArray<float> State;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FGymStateStruct Json")
		float Reward;

};


/**
 * 
 */
class RL_MODULE_API JsonHandler
{
public:
	JsonHandler();
	~JsonHandler();

	static TSharedPtr<FJsonObject> ReadJson(FString JsonString, bool& bSuccess);
	static FString CreateJson(TSharedPtr<FJsonObject> JsonObject, bool& bSuccess);

	static FGymCommandStruct ReadFGymCommandStruct(FString JsonString, bool& bSuccess);
	static FString CreateFGymCommandStruct(FGymCommandStruct StepStruct, bool& bSuccess);

	static FGymStateStruct ReadFGymStateStruct(FString JsonString, bool& bSuccess);
	static FString CreateFGymStateStruct(FGymStateStruct StepStruct, bool& bSuccess);

};
