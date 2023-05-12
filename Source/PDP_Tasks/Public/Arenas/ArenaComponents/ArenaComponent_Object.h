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
	
protected:
	// Scale params
	UPROPERTY()
	float Width;

	UPROPERTY()
	float Length;
	
	UPROPERTY()
	float Height;


	// Actor mesh setter
	UFUNCTION(BlueprintCallable, Category="Arena Components")
	void SetMesh(UStaticMesh* NewMesh);

	// Actor scale setter
	UFUNCTION(BlueprintCallable, Category="Arena Components")
	void SetScale(FVector NewScale);
	
private:
	// Actor mesh component
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* MeshComponent;
};
