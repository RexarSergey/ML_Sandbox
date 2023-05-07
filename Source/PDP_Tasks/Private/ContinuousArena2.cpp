// Fill out your copyright notice in the Description page of Project Settings.


#include "ContinuousArena2.h"

#include "Camera/CameraActor.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AContinuousArena2::AContinuousArena2()
{
}


void AContinuousArena2::SetFloorObject(const TSubclassOf<AActor>& NewFloor)
{
	FloorToSpawn = NewFloor;
}

void AContinuousArena2::SetTriggerObject(const TSubclassOf<AActor>& NewTrigger)
{
	TriggerToSpawn = NewTrigger;
}

void AContinuousArena2::SetArenaSize(float NewWidth, float NewLength, float NewHeight)
{
	Width = NewWidth;
	Length = NewLength;
	Height = NewHeight;
}

void AContinuousArena2::SetCameraPosition(float NewCameraHeight, float NewCameraRotation)
{
	CameraHeight = NewCameraHeight;
	CameraRotation = NewCameraRotation;
}


// Called when the game starts or when spawned
void AContinuousArena2::BeginPlay()
{
	Super::BeginPlay();

	if (!FloorToSpawn || !TriggerToSpawn) return;


	FVector ActorLoc = GetActorLocation();
	FRotator ActorRot = GetActorRotation();


	SpawnCamera(ActorLoc);
	SpawnFloor(ActorLoc, ActorRot);
	SpawnSpawnPoints(ActorLoc);
	SpawnTrigger(ActorLoc, ActorRot);
}

void AContinuousArena2::Destroyed()
{
	Super::Destroyed();

	if (Camera)
		Camera->Destroy();
	
	if (Floor)
		Floor->Destroy();

	if (Trigger)
		Trigger->Destroy();

	if (SpawnPoint1)
		SpawnPoint1->Destroy();

	if (SpawnPoint2)
		SpawnPoint2->Destroy();
}

void AContinuousArena2::GetSpawnPoint1Params(FVector& Location, FRotator& Rotation) const
{
	if (!SpawnPoint1) return;

	Location = SpawnPoint1->GetActorLocation();
	Rotation = SpawnPoint1->GetActorRotation();
}

void AContinuousArena2::GetSpawnPoint2Params(FVector& Location, FRotator& Rotation) const
{
	if (!SpawnPoint2) return;

	Location = SpawnPoint2->GetActorLocation();
	Rotation = SpawnPoint2->GetActorRotation();
}

void AContinuousArena2::SpawnCamera(const FVector Loc)
{
	// Camera initialization
	FVector CameraLoc = Loc;
	CameraLoc.Z = CameraLoc.Z + CameraHeight;


	FRotator CameraRot = UKismetMathLibrary::FindLookAtRotation(CameraLoc, Loc);
	CameraRot.Yaw = CameraRot.Yaw + CameraRotation;


	Camera = GetWorld()->SpawnActor<ACameraActor>(CameraLoc, CameraRot);
}

void AContinuousArena2::SpawnFloor(const FVector Loc, const FRotator Rot)
{
	// Floor initialization
	Floor = GetWorld()->SpawnActor<AActor>(FloorToSpawn, Loc, Rot);
	Floor->SetActorScale3D(FVector(Width, Length, Height));
}

void AContinuousArena2::SpawnSpawnPoints(const FVector Loc)
{
	// Spawn Points initialization
	FVector SPLoc1 = Loc;
	SPLoc1.X = SPLoc1.X + (Width * 50.f - 50.f);
	SPLoc1.Y = SPLoc1.Y - (Length * 50.f - 50.f);
	SPLoc1.Z = SPLoc1.Z + (Height * 50.f + 30.f);


	FVector SPLoc2 = Loc;
	SPLoc2.X = SPLoc2.X - (Width * 50.f - 50.f);
	SPLoc2.Y = SPLoc2.Y + (Length * 50.f - 50.f);
	SPLoc2.Z = SPLoc2.Z + (Height * 50.f + 30.f);


	const FRotator SPRot1 = UKismetMathLibrary::FindLookAtRotation(SPLoc1, Loc);
	const FRotator SPRot2 = UKismetMathLibrary::FindLookAtRotation(SPLoc2, Loc);


	SpawnPoint1 = GetWorld()->SpawnActor<ASpawnPointOnArena>(SPLoc1, SPRot1);
	SpawnPoint2 = GetWorld()->SpawnActor<ASpawnPointOnArena>(SPLoc2, SPRot2);
}

void AContinuousArena2::SpawnTrigger(const FVector Loc, const FRotator Rot)
{
	// Trigger initialization
	FVector ActorLoc = Loc;
	ActorLoc.Z = ActorLoc.Z + 100.f;


	Trigger = GetWorld()->SpawnActor<AActor>(TriggerToSpawn, ActorLoc, Rot);
	Trigger->SetActorScale3D(FVector(5.f, 5.f, 2.f));
	Trigger->SetHidden(false);
}

void AContinuousArena2::Init(const FVector Loc, const FRotator Rot)
{
	if (!FloorToSpawn || !TriggerToSpawn) return;


	SpawnCamera(Loc);
	SpawnFloor(Loc, Rot);
	SpawnSpawnPoints(Loc);
	SpawnTrigger(Loc, Rot);
}

float AContinuousArena2::GetLength()
{
	return Length;
}

void AContinuousArena2::Clear()
{
	if (Camera)
		Camera->Destroy();
	
	if (Floor)
		Floor->Destroy();

	if (Trigger)
		Trigger->Destroy();

	if (SpawnPoint1)
		SpawnPoint1->Destroy();

	if (SpawnPoint2)
		SpawnPoint2->Destroy();

	Destroy();
}
