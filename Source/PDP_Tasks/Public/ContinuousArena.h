// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ContinuousArena.generated.h"

UCLASS()
class PDP_TASKS_API AContinuousArena : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AContinuousArena();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ChangeArenaSize(float NewWidth = 10.f, float NewLength = 20.f, float NewHeight = 1.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Width = 10.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Length = 20.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Height = 1.f;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CameraHeight = 2200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CameraRotation = -90.f;

private:
	TArray<AActor*> ChildrenActors;

	void GetArenaParams();

};
