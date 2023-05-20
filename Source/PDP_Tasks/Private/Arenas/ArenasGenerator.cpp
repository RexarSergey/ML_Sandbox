#include "Arenas/ArenasGenerator.h"


// Sets default values
AArenasGenerator::AArenasGenerator()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	BoxComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AArenasGenerator::BeginPlay()
{
	Super::BeginPlay();
}

void AArenasGenerator::GenerateArenas(const bool bUseInputParam, const int ArenaNumber)
{
	DestroyArenas();

	if (!(ArenaToSpawn && FloorClass && SpawnPointClass && TriggerClass)) return;

	int Number = NumberToSpawn;
	if (bUseInputParam) Number = ArenaNumber;


	FVector Loc = GetActorLocation();
	const FRotator Rot = GetActorRotation();
	
	for (int i = 0; i < Number; ++i)
	{
		// Spawn new arena
		ASimpleArena* Arena = GetWorld()->SpawnActor<ASimpleArena>(ArenaToSpawn, Loc, Rot);
		// Setup arena components
		Arena->Init(FloorClass, SpawnPointClass, TriggerClass);

		// Change next spawn location
		Loc.Y = Loc.Y + (Arena->GetFloorScale().Y * 100.f) + 100.f + OptionalShift;

		// Add spawned arena into list
		ArenasList.Add(Arena);
	}
}

void AArenasGenerator::DestroyArenas()
{
	// Destroy all spawned arenas
	for (ASimpleArena* Arena : ArenasList)
	{
		Arena->Destroy();
	}

	// Clear list
	ArenasList.Empty();
}
