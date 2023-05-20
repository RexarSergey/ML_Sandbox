#pragma once

#include "CoreMinimal.h"
#include "ArenaComponents/ArenaComponent_Base.h"
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
	virtual void BeginPlay() override;

	// Floor components
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AArenaComponent_Base*> FloorList;

	// Wall components
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AArenaComponent_Base*> WallList;

	// Other components
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AArenaComponent_Base*> OtherList;

private:
	// Additional component to see actor on scene
	UPROPERTY()
	UBoxComponent* BoxComponent;

	// Setup floor components
	void SetupFloor();
	// Setup wall components
	void SetupWall();
	// Setup other components
	void SetupOther();
};
