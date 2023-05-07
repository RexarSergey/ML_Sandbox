// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SpawnPointOnArena.generated.h"

UCLASS()
class PDP_TASKS_API ASpawnPointOnArena : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASpawnPointOnArena();

	UFUNCTION()
	bool GetIsPossessed() const;

	UFUNCTION()
	void SetIsPossessed(bool NewPossessed);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsPossessed = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxComponent;
	
};
