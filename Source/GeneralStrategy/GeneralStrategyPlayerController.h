// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"

#include "GeneralStrategySpectatorPawn.h"

#include "GeneralStrategyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GENERALSTRATEGY_API AGeneralStrategyPlayerController : public APlayerController
{
	GENERATED_BODY()
		AGeneralStrategyPlayerController();

	public:
		UFUNCTION()
			virtual void SetupInputComponent() override;

		UFUNCTION()
			void AddToSelection(AActor* Selected);

		UFUNCTION()
			void LeftMousePressed();

		UFUNCTION()
			void LeftMouseReleased();

		UFUNCTION()
			void RightMousePressed();

		UFUNCTION()
			void RightMouseReleased();

		UFUNCTION()
			virtual void Tick(float DeltaSeconds) override;

	private:
		TArray<AActor*> CurrentSelection;

		AGeneralStrategySpectatorPawn* CurrentPawn;

		FVector2D MousePosition,
				  MouseVelocity;
};