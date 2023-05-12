// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ConstructableArena.generated.h"

UCLASS()
class PDP_TASKS_API AConstructableArena : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AConstructableArena();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
