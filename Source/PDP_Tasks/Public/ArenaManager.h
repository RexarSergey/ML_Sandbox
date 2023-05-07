// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ContinuousArena2.h"
#include "ArenaManager.generated.h"

UCLASS()
class PDP_TASKS_API AArenaManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AArenaManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	UFUNCTION(BlueprintCallable)
	void GenerateArenas(int ArenaCount);

	UFUNCTION(BlueprintCallable)
	void DeleteArenas();


	// Arena size
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Width = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Length = 20.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Height = 1.f;


	// Camera params
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CameraHeight = 2200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CameraRotation = -90.f;


	// Arena manager params
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ArenaNumber = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OptionalShift = 100.f;
	

	// Objects to spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> Floor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> Trigger;

private:
	UPROPERTY()
	TArray<AContinuousArena2*> ArenaList;
};
