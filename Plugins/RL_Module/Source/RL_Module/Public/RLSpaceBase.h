// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RLEnums.h"
#include "RLSpaceBase.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct RL_MODULE_API FRLSpaceBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gym Space")
		TArray<float> Low;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gym Space")
		TArray<float> High;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gym Space")
	TEnumAsByte<ESpaceEnum> Space;

};
