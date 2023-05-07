// Fill out your copyright notice in the Description page of Project Settings.


#include "ArenaManager.h"

#include "LevelEditorViewport.h"
#include "Components/BoxComponent.h"

// Sets default values
AArenaManager::AArenaManager()
{
}

// Called when the game starts or when spawned
void AArenaManager::BeginPlay()
{
	Super::BeginPlay();
}

void AArenaManager::GenerateArenas(const int ArenaCount)
{
	DeleteArenas();

	FVector ActorLoc = GetActorLocation();
	const FRotator ActorRot = GetActorRotation();


	for (int i = 0; i < ArenaCount; ++i)
	{
		AContinuousArena2* ArenaRef = GetWorld()->SpawnActor<AContinuousArena2>(ActorLoc, ActorRot);


		ArenaRef->SetFloorObject(Floor);
		ArenaRef->SetTriggerObject(Trigger);
		ArenaRef->SetArenaSize(Width, Length, Height);
		ArenaRef->SetCameraPosition(CameraHeight, CameraRotation);
		ArenaRef->Init(ActorLoc, ActorRot);		


		ActorLoc.Y = ActorLoc.Y + (Length * 100.f) + 100.f + OptionalShift;


		ArenaList.Add(ArenaRef);
	}
}

void AArenaManager::DeleteArenas()
{
	for (AContinuousArena2* Arena : ArenaList)
	{
		Arena->Clear();
	}

	ArenaList.Empty();
}
