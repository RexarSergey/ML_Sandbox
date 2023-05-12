#pragma once

#include "CoreMinimal.h"
#include "AC_Utils.h"
#include "Arenas/ArenaComponents/ArenaComponent_Object.h"
#include "ArenaComponent_ConstructableObj.generated.h"



UCLASS()
class PDP_TASKS_API AArenaComponent_ConstructableObj : public AArenaComponent_Object
{
	GENERATED_BODY()
public:
	AArenaComponent_ConstructableObj();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Arena Components")
	FConnections ComponentConnection;

	UFUNCTION(BlueprintCallable, Category="Arena Components")
	void FixAllConnections();

private:
	void FixConnection(EConnectionDirection Direction, FConstructableComponent Connection);
	FVector FixLocation(EConnectionDirection Direction) const;
	void CheckConnections(EConnectionDirection Direction, AArenaComponent_ConstructableObj* ConstructableObj);
};

