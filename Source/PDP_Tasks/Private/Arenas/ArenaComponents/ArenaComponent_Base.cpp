#include "Arenas/ArenaComponents/ArenaComponent_Base.h"


// Sets default values
AArenaComponent_Base::AArenaComponent_Base()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	BoxComponent->SetupAttachment(RootComponent);

	Type = Base;
}

// Return component type
EArenaComponentType AArenaComponent_Base::GetComponentType() const
{
	return Type;
}

