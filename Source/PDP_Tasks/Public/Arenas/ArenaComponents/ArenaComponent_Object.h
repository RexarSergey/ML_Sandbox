#pragma once

#include "CoreMinimal.h"
#include "Arenas/ArenaComponents/ArenaComponent_Base.h"
#include "ArenaComponent_Object.generated.h"


UCLASS()
class PDP_TASKS_API AArenaComponent_Object : public AArenaComponent_Base
{
	GENERATED_BODY()

public:
	AArenaComponent_Object();

	// Actor mesh setter
	UFUNCTION(BlueprintCallable, Category="Arena Components")
	void SetNewObjectMesh(UStaticMesh* NewMesh);

	// Actor scale setter
	UFUNCTION(BlueprintCallable, Category="Arena Components")
	void SetNewObjectScale(FVector NewScale);
	
protected:
	virtual void BeginPlay() override;
	
	// Scale params
	UPROPERTY()
	float Width;

	UPROPERTY()
	float Length;
	
	UPROPERTY()
	float Height;
	
private:
	// Actor mesh component
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* MeshComponent;
};
