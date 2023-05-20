#pragma once

#include "CoreMinimal.h"
#include "ArenaComponents/ArenaComponent_Base.h"
#include "ArenaComponents/ArenaComponent_Object.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "SimpleArena.generated.h"


UCLASS()
class PDP_TASKS_API ASimpleArena : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASimpleArena();

	/**
	 * @brief Setup components
	 * @param FloorClass Floor component
	 * @param SpawnPointsClass SpawnPoint component
	 * @param TriggerClass Trigger component
	 */
	void Init(TSubclassOf<AArenaComponent_Object> FloorClass,
	          TSubclassOf<AArenaComponent_Base> SpawnPointsClass,
	          TSubclassOf<AArenaComponent_Base> TriggerClass);

	FVector GetFloorScale() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Custom destructor
	virtual void Destroyed() override;

	// Components classes to spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Simple Arena Floor")
	TSubclassOf<AArenaComponent_Object> FloorToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Simple Arena SpawnPoints")
	TSubclassOf<AArenaComponent_Base> SpawnPointsToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Simple Arena Trigger")
	TSubclassOf<AArenaComponent_Base> TriggerToSpawn;


	// Scalable params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Simple Arena Floor")
	float FloorWidth = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Simple Arena Floor")
	float FloorLength = 20.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Simple Arena Floor")
	float FloorHeight = 1.f;


	// Number of SpawnPoints to spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Simple Arena SpawnPoints")
	int SpawnPointNumber = 2;


	UPROPERTY(BlueprintReadOnly, Category="Simple Arena SpawnPoints")
	FSpawnPointsPositions SpawnPointsPositions;

private:
	// Setup functions
	void SetupFloorComponent();
	void SetupSpawnPointComponents();
	void SetupTriggerComponent();


	// Calculate SpawnPoints positions to spawn
	void CalculateSpawnPointPositions();


	// Additional component to see actor on scene
	UPROPERTY()
	UBoxComponent* BoxComponent;

	// Arena Floor component
	UPROPERTY()
	AArenaComponent_Object* Floor;

	// Arena SpawnPoint components
	UPROPERTY()
	TArray<AArenaComponent_Base*> SpawnPoints;

	UPROPERTY()
	AArenaComponent_Base* Trigger;
};
