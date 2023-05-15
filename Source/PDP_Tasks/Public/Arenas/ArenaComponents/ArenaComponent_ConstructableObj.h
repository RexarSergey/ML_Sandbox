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
	// Connect the components together
	UFUNCTION(BlueprintCallable, Category="Arena Components")
	void FixAllConnections();
	
protected:
	// Components connections with another ones
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Arena Components")
	FConnections ComponentConnection;

	// Flag to prevent re-fixing
	bool bIsFixed = false;

private:
	// Fix the connection in a certain direction and call fix function in other components
	void FixConnection(EConnectionDirection Direction, FComponentInfo Connection);

	// Fix the components location in a certain direction
	void FixLocation(EConnectionDirection Direction, AArenaComponent_ConstructableObj* ConstructableObj) const;

	// Check and add connection between components
	void CheckConnections(EConnectionDirection Direction, AArenaComponent_ConstructableObj* ConstructableObj);
};

