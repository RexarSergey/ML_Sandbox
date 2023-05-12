#pragma once

#include "CoreMinimal.h"
#include "AC_Utils.generated.h"


UENUM(BlueprintType)
enum EArenaComponentType
{
	Base			UMETA(DisplayName = "Base Arena Component"),
	Floor			UMETA(DisplayName = "Floor Arena Component"),
	Wall			UMETA(DisplayName = "Wall Arena Component"),
	SpawnPoint		UMETA(DisplayName = "Spawn Point Arena Component"),
	Other			UMETA(DisplayName = "Other Arena Component")
};

UENUM()
enum EConnectionDirection
{
	Up,
	Down,
	Left,
	Right
};

USTRUCT(BlueprintType)
struct FConstructableComponent
{
	GENERATED_BODY();
	
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Struct Arena Component")
	// bool bIsEmpty = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Struct Arena Component")
	bool bIsCatched = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Struct Arena Component")
	AActor* ConstructableObj;
};


USTRUCT(BlueprintType)
struct FConnections
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Struct Connections")
	FConstructableComponent UpConnection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Struct Connections")
	FConstructableComponent DownConnection;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Struct Connections")
	FConstructableComponent LeftConnection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Struct Connections")
	FConstructableComponent RightConnection;
};
