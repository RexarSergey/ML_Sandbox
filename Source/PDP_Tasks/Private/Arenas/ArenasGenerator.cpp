// Fill out your copyright notice in the Description page of Project Settings.


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
		ASimpleArena* Arena = GetWorld()->SpawnActor<ASimpleArena>(ArenaToSpawn, Loc, Rot);
		Arena->Init(FloorClass, SpawnPointClass, TriggerClass);

		Loc.Y = Loc.Y + (Arena->GetFloorScale().Y * 100.f) + 100.f + OptionalShift;
		
		ArenasList.Add(Arena);
	}
}

void AArenasGenerator::DestroyArenas()
{
	for (ASimpleArena* Arena : ArenasList)
	{
		Arena->Destroy();
	}

	ArenasList.Empty();
}
