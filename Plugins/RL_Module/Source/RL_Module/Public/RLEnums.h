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
	GetDQNLearning UMETA(DisplayName = "Get Network (RL Model)")

};


UENUM(BlueprintType)
enum EPolicy
{
	BoltzmannQPolicy     UMETA(DisplayName = "Boltzmann QPolicy"),
	EpsGreedyQPolicy	 UMETA(DisplayName = "EpsGreedy QPolicy"),
	SoftmaxPolicy		 UMETA(DisplayName = "Softmax Policy"),
	GreedyQPolicy		 UMETA(DisplayName = "Greedy QPolicy"),
	MaxBoltzmannQPolicy  UMETA(DisplayName = "Max Boltzmann QPolicy"),
};

UENUM(BlueprintType)
enum EMetric
{
	MAE     UMETA(DisplayName = "mae"),
	MSE		UMETA(DisplayName = "mse"),
	RMSE    UMETA(DisplayName = "rmse"),
	MSLE	UMETA(DisplayName = "msle"),
	LCE     UMETA(DisplayName = "lce"),
};


UENUM(BlueprintType)
enum EOptimizer
{
	Adam     UMETA(DisplayName = "Adam"),
	RMSprop		UMETA(DisplayName = "RMSprop"),
	SGD    UMETA(DisplayName = "SGD"),
};
