// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JsonHandler.generated.h"


USTRUCT(BlueprintType)
struct RL_MODULE_API FPythonCommandStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FPythonCommandStruct Json")
	int32 id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FPythonCommandStruct Json")
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


USTRUCT(BlueprintType)
struct RL_MODULE_API FDQNLearningStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FDQNLearningStruct Json")
		TArray<int32> Network;

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

	static FPythonCommandStruct ReadFGymCommandStruct(FString JsonString, bool& bSuccess);
	static FString CreateFPythonCommandStruct(FPythonCommandStruct StepStruct, bool& bSuccess);

	static FGymStateStruct ReadFGymStateStruct(FString JsonString, bool& bSuccess);
	static FString CreateFGymStateStruct(FGymStateStruct StepStruct, bool& bSuccess);

	static FDQNLearningStruct ReadFDQNLearningStruct(FString JsonString, bool& bSuccess);
	static FString CreateFDQNLearningStruct(FDQNLearningStruct StepStruct, bool& bSuccess);

};
