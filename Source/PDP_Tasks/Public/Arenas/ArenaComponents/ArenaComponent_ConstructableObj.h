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
	// Connect other components together
	UFUNCTION(BlueprintCallable, Category="Arena Components")
	void FixAllConnections();
	
protected:
	// Component connections with another ConstructableObj
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Arena Components")
	FConnections ComponentConnection;

	// Flag to prevent re-fixing
	bool bIsFixed = false;

private:
	/**
	 * @brief Fix the connection in a certain direction and call fix function in other components
	 * @param Direction Connection direction type (Up, Down, Left, Right)
	 * @param Connection Connection from struct
	 */
	void FixConnection(EConnectionDirection Direction, FComponentInfo Connection);

	/**
	 * @brief Fix the components location in a certain direction
	 * @param Direction Connection direction type (Up, Down, Left, Right)
	 * @param ConstructableObj Component, that connected with current one
	 */
	void FixLocation(EConnectionDirection Direction, AArenaComponent_ConstructableObj* ConstructableObj) const;
	
	/**
	 * @brief Check and add connection between components
	 * @param Direction Connection direction type (Up, Down, Left, Right)
	 * @param ConstructableObj Component, that connected with current one
	 */
	void CheckConnections(EConnectionDirection Direction, AArenaComponent_ConstructableObj* ConstructableObj);
};

