#include "Arenas/Arena_Base.h"


// Sets default values
AArena_Base::AArena_Base()
{
	// Creating Mesh Component for the class
	FloorMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube Mesh"));

	// Try find Cube Mesh
	ConstructorHelpers::FObjectFinder<UStaticMesh> FindMesh
		(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));

	// Set Mesh if Succeeded
	if (FindMesh.Succeeded())
	{
		FloorMeshComponent->SetStaticMesh(FindMesh.Object);
	}

	RootComponent = FloorMeshComponent;
}

// Called when the game starts or when spawned
void AArena_Base::BeginPlay()
{
	Super::BeginPlay();
}

void AArena_Base::ChangeFloorMesh_Implementation(UStaticMesh* NewMesh)
{
	FloorMeshComponent->SetStaticMesh(NewMesh);
	RootComponent = FloorMeshComponent;
}

void AArena_Base::ChangeFloorScale_Implementation(const float Width = 10.f, const float Length = 20.f,
                                                  const float Height = 1.f)
{
	if (Width > 0.f && Length > 0.f && Height > 0.f)
	{
		SetActorScale3D(FVector3d(Width, Length, Height));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Arena Scale must be positive!"));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Arena Scale must be positive!"));
	}
}
