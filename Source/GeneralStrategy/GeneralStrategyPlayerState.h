// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerState.h"
#include "GeneralStrategyPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class GENERALSTRATEGY_API AGeneralStrategyPlayerState : public APlayerState
{
	GENERATED_BODY()
		AGeneralStrategyPlayerState();

	public:
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player Starting Statistics")
			int32 StartingCollectedResource;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player Starting Statistics")
			int32 StartingGeneratedResource;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player Starting Statistics")
			int32 StartingPopulation;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player Max Statistics")
			int32 MaxCollectedResource;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player Max Statistics")
			int32 MaxGeneratedResource;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player Max Statistics")
			int32 MaxPopulation;

	private:	
		uint32 CurrentCollectedResource,
			   CurrentGeneratedResource,
			   CurrentPopulation;
};
