// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 *
 */
UENUM()
enum ESpaceEnum
{
	BoxSpace         UMETA(DisplayName = "Box Space (Gym)"),
	DiscreteSpace    UMETA(DisplayName = "Discrete Space (Gym)")
};

UENUM()
enum ECommandEnum
{
	Step         UMETA(DisplayName = "Step (Gym)"),
	Reset        UMETA(DisplayName = "Reset (Gym)"),
	State        UMETA(DisplayName = "State (Gym)"),
	Reward        UMETA(DisplayName = "Reward (Gym)"),
	IsDone        UMETA(DisplayName = "Done (Gym)"),

};


