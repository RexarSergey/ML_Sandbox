#include "ContinuousArena.h"

#include "Camera/CameraActor.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AContinuousArena::AContinuousArena()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AContinuousArena::BeginPlay()
{
	Super::BeginPlay();

	GetArenaParams();


	FVector Loc = GetActorLocation();
	Loc.Z = Loc.Z + CameraHeight;
	FRotator Rot = UKismetMathLibrary::FindLookAtRotation(Loc, GetActorLocation());
	Rot.Yaw = Rot.Yaw + CameraRotation;
	FActorSpawnParameters Parameters;
	GetWorld()->SpawnActor<ACameraActor>(Loc, Rot, Parameters);
}

void AContinuousArena::ChangeArenaSize(float NewWidth, float NewLength, float NewHeight)
{
	if (!ChildrenActors.IsEmpty())
	{
		Width = NewWidth;
		Length = NewLength;
		Height = NewHeight;

		ChildrenActors[0]->SetActorLocation(this->GetActorLocation());
	}
}

void AContinuousArena::GetArenaParams()
{
	GetAttachedActors(ChildrenActors);

	if (!ChildrenActors.IsEmpty())
	{
		FVector ArenaSize = ChildrenActors[0]->GetActorScale3D();

		Width = ArenaSize.X;
		Length = ArenaSize.Y;
		Height = ArenaSize.Z;

		ChildrenActors[0]->SetActorLocation(this->GetActorLocation());
	}
}
