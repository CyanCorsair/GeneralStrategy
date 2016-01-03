// Fill out your copyright notice in the Description page of Project Settings.

#include "GeneralStrategy.h"
#include "GeneralStrategyPlayerState.h"

AGeneralStrategyPlayerState::AGeneralStrategyPlayerState()
{
	StartingCollectedResource = 100;
	StartingGeneratedResource = 50;
	StartingPopulation = 0;

	CurrentCollectedResource = StartingCollectedResource;
	CurrentGeneratedResource = StartingGeneratedResource;
	CurrentPopulation = StartingPopulation;

	MaxCollectedResource = 500;
	MaxGeneratedResource = 100;
	MaxPopulation = 64;
}