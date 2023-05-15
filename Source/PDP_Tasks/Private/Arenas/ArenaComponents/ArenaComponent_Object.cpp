#include "Arenas/ArenaComponents/ArenaComponent_Object.h"


AArenaComponent_Object::AArenaComponent_Object()
{
	// Creating Mesh Component for the actor
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube Mesh"));

	// Try find Cube Mesh
	const ConstructorHelpers::FObjectFinder<UStaticMesh> FoundMesh
		(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));

	// Set Mesh if Succeeded
	if (FoundMesh.Succeeded())
	{
		MeshComponent->SetStaticMesh(FoundMesh.Object);
	}

	RootComponent = MeshComponent;

	Type = Other;
}

void AArenaComponent_Object::BeginPlay()
{
	Super::BeginPlay();

	// Get scale params from scene
	Width = GetActorScale3D().X;
	Length = GetActorScale3D().Y;
	Height = GetActorScale3D().Z;
}

void AArenaComponent_Object::SetNewObjectMesh(UStaticMesh* NewMesh)
{
	// Set new mesh for component
	MeshComponent->SetStaticMesh(NewMesh);
	// Update RootComponent
	RootComponent = MeshComponent;
}

void AArenaComponent_Object::SetNewObjectScale(const FVector NewScale)
{
	// Set new scale for component
	SetActorScale3D(NewScale);

	// Update scale params
	Width = NewScale.X;
	Length = NewScale.Y;
	Height = NewScale.Z;
}
