#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/ConstructorHelpers.h"
#include "Arena_Base.generated.h"

UCLASS()
class PDP_TASKS_API AArena_Base : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AArena_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UFUNCTION(Client, Reliable, BlueprintCallable, Category="Arena")
	void ChangeFloorMesh(UStaticMesh* NewMesh);

	UFUNCTION(Client, Reliable, BlueprintCallable, Category="Arena")
	void ChangeFloorScale(float Width, float Length, float Height);

private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* FloorMeshComponent;
};
