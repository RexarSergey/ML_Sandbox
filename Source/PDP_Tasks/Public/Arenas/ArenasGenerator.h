#pragma once

#include "CoreMinimal.h"
#include "SimpleArena.h"
#include "GameFramework/Actor.h"
#include "ArenasGenerator.generated.h"


UCLASS()
class PDP_TASKS_API AArenasGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArenasGenerator();

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/**
	 * @brief Generate multiply arenas
	 * @param bUseInputParam Flag defining using ArenaNumber input or not
	 * @param ArenaNumber Arena number input
	 */
	UFUNCTION(BlueprintCallable, Category="Arena Generator")
	void GenerateArenas(bool bUseInputParam, int ArenaNumber);

	// Destroying all generated arenas
	UFUNCTION(BlueprintCallable, Category="Arena Generator")
	void DestroyArenas();
	
	// Arena generator params
	// Arena class to spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Arena Generator Params")
	TSubclassOf<ASimpleArena> ArenaToSpawn;
	// Number arenas to spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Arena Generator Params")
	int NumberToSpawn = 1;
	// Shift between spawned arenas
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Arena Generator Params")
	float OptionalShift = 100.f;


	// Arena components classes to spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Arena Params")
	TSubclassOf<AArenaComponent_Object> FloorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Arena Params")
	TSubclassOf<AArenaComponent_Base> SpawnPointClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Arena Params")
	TSubclassOf<AArenaComponent_Base> TriggerClass;
	

private:
	// Additional component to see actor on scene
	UPROPERTY()
	UBoxComponent* BoxComponent;

	// Spawned arenas list
	UPROPERTY()
	TArray<ASimpleArena*> ArenasList;
};
