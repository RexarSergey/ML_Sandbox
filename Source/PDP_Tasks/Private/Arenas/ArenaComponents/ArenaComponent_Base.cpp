#include "Arenas/ArenaComponents/ArenaComponent_Base.h"


// Sets default values
AArenaComponent_Base::AArenaComponent_Base()
{
	// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Base"));
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	BoxComponent->SetupAttachment(RootComponent);

	Type = Base;
}

EArenaComponentType AArenaComponent_Base::GetComponentType() const
{
	return Type;
}

