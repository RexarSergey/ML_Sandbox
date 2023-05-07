// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RLSpaceBase.h"
#include "RLEnviromentBase.generated.h"


UCLASS()
class RL_MODULE_API ARLEnviromentBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARLEnviromentBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Gym Enviroment")
	void Step();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Gym Enviroment")
	void Reset();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Gym Enviroment")
	TArray<float> GetState();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Gym Enviroment")
	float GetReward();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Gym Enviroment")
	bool IsDone();

	virtual void Step_Implementation() {};

	virtual void Reset_Implementation() {};

	virtual TArray<float> GetState_Implementation() { return TArray<float>(); };

	virtual float GetReward_Implementation() { return 0.f; };

	virtual bool IsDone_Implementation() { return true; };


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Observation Space")
	FRLSpaceBase ObservationSpace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Action Space")
	FRLSpaceBase ActionSpace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Action Space")
	TArray<float> Action;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Network")
		TArray<int32> NetworkNeurones;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Network")
		TArray<FString> NetworkActivations;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Learn")
		float LearningRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Learn")
		int32 Steps;
};
