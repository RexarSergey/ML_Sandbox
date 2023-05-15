#pragma once

#include "CoreMinimal.h"
#include "AC_Utils.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "ArenaComponent_Base.generated.h"


UCLASS()
class PDP_TASKS_API AArenaComponent_Base : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AArenaComponent_Base();

	// Type getter
	EArenaComponentType GetComponentType() const;

protected:
	// Component Type
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Arena Components")
	TEnumAsByte<EArenaComponentType> Type;

private:
	// Additional component to see actor on scene
	UPROPERTY()
	UBoxComponent* BoxComponent;
};
