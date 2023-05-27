// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RLEnums.h"
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
		bool IsDone = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FGymStateStruct Json")
		TArray<float> State;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FGymStateStruct Json")
		float Reward = .0f;

};


USTRUCT(BlueprintType)
struct RL_MODULE_API FDQNLearningStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite,  DisplayName = "ObservationSpace Low", Category = "Gym Space Box (ObservationSpace)")
	TArray<float> Low;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "ObservationSpace High", Category = "Gym Space Box (ObservationSpace)")
	TArray<float> High;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gym Space Box (ActionSpace)")
		int32 ActionLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Learn")
		TArray<int32> Network;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Learn")
		TArray<FString> Activations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Learn")
		TEnumAsByte<EOptimizer> Optimizer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Learn")
		float LearningRate = 0.01;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Learn")
		int32 Steps = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Learn")
		int32 StepsWarmup = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Learn")
		float TargetModelUpdate = 1e-3f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Learn")
		TArray<TEnumAsByte<EMetric>> Metrics;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Policy")
		TEnumAsByte<EPolicy> Policy;



};

USTRUCT(BlueprintType)
struct RL_MODULE_API FGymStruct
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
