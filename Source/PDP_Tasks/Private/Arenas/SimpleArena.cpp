#include "Arenas/SimpleArena.h"

#include "Arenas/ArenaComponents/ArenaComponent_Object.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ASimpleArena::ASimpleArena()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	BoxComponent->SetupAttachment(RootComponent);
}

void ASimpleArena::Init(TSubclassOf<AArenaComponent_Object> FloorClass,
                        TSubclassOf<AArenaComponent_Base> SpawnPointsClass,
                        TSubclassOf<AArenaComponent_Base> TriggerClass)
{
	FloorToSpawn = FloorClass;
	SpawnPointsToSpawn = SpawnPointsClass;
	TriggerToSpawn = TriggerClass;

	SetupFloorComponent();
	SetupSpawnPointComponents();
	SetupTriggerComponent();
}

FVector ASimpleArena::GetFloorScale() const
{
	return FVector(FloorWidth, FloorLength, FloorHeight);
}

// Called when the game starts or when spawned
void ASimpleArena::BeginPlay()
{
	Super::BeginPlay();

	if (!FloorToSpawn) return;

	SetupFloorComponent();
	SetupSpawnPointComponents();
	SetupTriggerComponent();
}

// Called when actor destroyed
void ASimpleArena::Destroyed()
{
	Super::Destroyed();

	// Destroy all spawned actors
	if (BoxComponent) BoxComponent->DestroyComponent();

	if (Floor) Floor->Destroy();

	if (!SpawnPoints.IsEmpty())
	{
		for (AArenaComponent_Base* Actor : SpawnPoints)
		{
			Actor->Destroy();
		}
		SpawnPoints.Empty();
	}

	if (Trigger) Trigger->Destroy();
}

void ASimpleArena::SetupFloorComponent()
{
	// Spawn Floor component based on selected class FloorClassToSpawn
	Floor = GetWorld()->SpawnActor<AArenaComponent_Object>(FloorToSpawn, GetActorLocation(), GetActorRotation());
	Floor->SetNewObjectScale(FVector(FloorWidth, FloorLength, FloorHeight));

	CalculateSpawnPointPositions();
}

void ASimpleArena::SetupSpawnPointComponents()
{
	if (!SpawnPointsToSpawn) return;


	if (SpawnPointNumber < 1) SpawnPointNumber = 1;
	if (SpawnPointNumber > 4) SpawnPointNumber = 4;


	for (int i = 0; i < SpawnPointNumber; ++i)
	{
		// Initializing SpawnPoint location and rotation from structure
		FVector Loc = SpawnPointsPositions.SpawnPointInfos[i].Location;
		FRotator Rot = SpawnPointsPositions.SpawnPointInfos[i].Rotation;

		// Spawn SpawnPoint component based on selected class SpawnPointsToSpawn
		AArenaComponent_Base* SpawnPoint = GetWorld()->SpawnActor<AArenaComponent_Base>(SpawnPointsToSpawn, Loc, Rot);
		// Add spawned SpawnPoint into SpawnPoints array
		SpawnPoints.Add(SpawnPoint);
	}
}

void ASimpleArena::SetupTriggerComponent()
{
	if (!TriggerToSpawn) return;

	FVector Loc = GetActorLocation();
	Loc.Z = Loc.Z + 50.f;

	// Spawn Trigger component based on selected class TriggerToSpawn
	Trigger = GetWorld()->SpawnActor<AArenaComponent_Base>(TriggerToSpawn, Loc, GetActorRotation());
}

void ASimpleArena::CalculateSpawnPointPositions()
{
	constexpr float ShiftFromEdge = 75.f;

	// Positions on X axis
	const float XUp = GetActorLocation().X + (FloorWidth * 50.f - ShiftFromEdge);
	const float XDown = GetActorLocation().X - (FloorWidth * 50.f - ShiftFromEdge);

	// Positions on Y axis
	const float YLeft = GetActorLocation().Y - (FloorLength * 50.f - ShiftFromEdge);
	const float YRight = GetActorLocation().Y + (FloorLength * 50.f - ShiftFromEdge);

	const float Z = GetActorLocation().Z + (FloorHeight * 50.f + 30.f);

	// Creating SpawnPoint infos
	FSpawnPointInfo SpawnPoint1;
	FSpawnPointInfo SpawnPoint2;
	FSpawnPointInfo SpawnPoint3;
	FSpawnPointInfo SpawnPoint4;


	// Filling parameters
	SpawnPoint1.Location = FVector(XUp, YLeft, Z);
	SpawnPoint1.Rotation = UKismetMathLibrary::FindLookAtRotation(
		SpawnPoint1.Location, GetActorLocation());

	SpawnPoint2.Location = FVector(XDown, YRight, Z);
	SpawnPoint2.Rotation = UKismetMathLibrary::FindLookAtRotation(
		SpawnPoint2.Location, GetActorLocation());

	SpawnPoint3.Location = FVector(XUp, YRight, Z);
	SpawnPoint3.Rotation = UKismetMathLibrary::FindLookAtRotation(
		SpawnPoint3.Location, GetActorLocation());

	SpawnPoint4.Location = FVector(XDown, YLeft, Z);
	SpawnPoint4.Rotation = UKismetMathLibrary::FindLookAtRotation(
		SpawnPoint4.Location, GetActorLocation());


	// Adding infos in structure
	SpawnPointsPositions.SpawnPointInfos.Add(SpawnPoint1);
	SpawnPointsPositions.SpawnPointInfos.Add(SpawnPoint2);
	SpawnPointsPositions.SpawnPointInfos.Add(SpawnPoint3);
	SpawnPointsPositions.SpawnPointInfos.Add(SpawnPoint4);
}
