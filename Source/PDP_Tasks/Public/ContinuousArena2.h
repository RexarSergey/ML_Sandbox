// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnPointOnArena.h"
#include "ContinuousArena2.generated.h"

UCLASS()
class PDP_TASKS_API AContinuousArena2 : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AContinuousArena2();


	void SetFloorObject(const TSubclassOf<AActor>& NewFloor);

	void SetTriggerObject(const TSubclassOf<AActor>& NewTrigger);

	void SetArenaSize(float NewWidth, float NewLength, float NewHeight);

	void SetCameraPosition(float NewCameraHeight, float NewCameraRotation);

	void Init(FVector Loc, FRotator Rot);

	float GetLength();

	void Clear();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Destroyed() override;

	// Get Spawn Points params
	UFUNCTION(BlueprintCallable, Category = "Spawn Point")
	void GetSpawnPoint1Params(FVector& Location, FRotator& Rotation) const;

	UFUNCTION(BlueprintCallable, Category = "Spawn Point")
	void GetSpawnPoint2Params(FVector& Location, FRotator& Rotation) const;


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


	// Objects to use
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> FloorToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> TriggerToSpawn;


	// Spawned objects
	UPROPERTY(BlueprintReadOnly)
	ACameraActor* Camera;

	UPROPERTY(BlueprintReadOnly)
	AActor* Floor;

	UPROPERTY(BlueprintReadOnly)
	AActor* Trigger;

	UPROPERTY(BlueprintReadOnly)
	ASpawnPointOnArena* SpawnPoint1;

	UPROPERTY(BlueprintReadOnly)
	ASpawnPointOnArena* SpawnPoint2;

private:
	void SpawnCamera(FVector Loc);

	void SpawnFloor(FVector Loc, FRotator Rot);

	void SpawnSpawnPoints(FVector Loc);

	void SpawnTrigger(FVector Loc, FRotator Rot);
};
