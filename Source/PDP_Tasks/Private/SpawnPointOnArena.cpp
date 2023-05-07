// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPointOnArena.h"

#include "Components/BoxComponent.h"
#include "EnvironmentQuery/EnvQueryTypes.h"

// Sets default values
ASpawnPointOnArena::ASpawnPointOnArena()
{
 	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxComponent->SetupAttachment(RootComponent);
	
}

bool ASpawnPointOnArena::GetIsPossessed() const
{
	return IsPossessed;
}

void ASpawnPointOnArena::SetIsPossessed(bool NewPossessed)
{
	IsPossessed = NewPossessed;
}

// Called when the game starts or when spawned
void ASpawnPointOnArena::BeginPlay()
{
	Super::BeginPlay();
	
}
