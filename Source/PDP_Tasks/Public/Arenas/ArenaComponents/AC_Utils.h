#pragma once

#include "CoreMinimal.h"
#include "AC_Utils.generated.h"


// Component types
UENUM(BlueprintType)
enum EArenaComponentType
{
	Base			UMETA(DisplayName = "Base Arena Component"),
	Floor			UMETA(DisplayName = "Floor Arena Component"),
	Wall			UMETA(DisplayName = "Wall Arena Component"),
	SpawnPoint		UMETA(DisplayName = "Spawn Point Arena Component"),
	Other			UMETA(DisplayName = "Other Arena Component")
};

// Components connection directions
UENUM()
enum EConnectionDirection
{
	Up,
	Down,
	Left,
	Right
};


USTRUCT(BlueprintType)
struct FComponentInfo
{
	GENERATED_BODY();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Struct Arena Component")
	AActor* ConstructableObj;
};


USTRUCT(BlueprintType)
struct FConnections
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Struct Connections")
	FComponentInfo UpConnection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Struct Connections")
	FComponentInfo DownConnection;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Struct Connections")
	FComponentInfo LeftConnection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Struct Connections")
	FComponentInfo RightConnection;
};
