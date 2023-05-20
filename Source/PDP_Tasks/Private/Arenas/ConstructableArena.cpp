#include "Arenas/ConstructableArena.h"
#include "Arenas/ArenaComponents/ArenaComponent_ConstructableObj.h"


AConstructableArena::AConstructableArena()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	BoxComponent->SetupAttachment(RootComponent);
}

void AConstructableArena::BeginPlay()
{
	Super::BeginPlay();

	SetupFloor();
	SetupWall();
	SetupOther();
}

void AConstructableArena::SetupFloor()
{
	// If empty do nothing
	if (FloorList.IsEmpty()) return;

	for (AArenaComponent_Base* Component : FloorList)
	{
		AArenaComponent_ConstructableObj* ConstructableObj = Cast<AArenaComponent_ConstructableObj>(Component);
		ConstructableObj->FixAllConnections();
	}
}

void AConstructableArena::SetupWall()
{
	// If empty do nothing
	if (WallList.IsEmpty()) return;

	for (AArenaComponent_Base* Component : WallList)
	{
		AArenaComponent_ConstructableObj* ConstructableObj = Cast<AArenaComponent_ConstructableObj>(Component);
		ConstructableObj->FixAllConnections();
	}
}

void AConstructableArena::SetupOther()
{
	// If empty do nothing
	if (OtherList.IsEmpty()) return;

	for (AArenaComponent_Base* Component : OtherList)
	{
		Component->SetActorLocation(GetActorLocation());
	}
}
