// Fill out your copyright notice in the Description page of Project Settings.

#include "GeneralStrategy.h"
#include "GeneralStrategyGameMode.h"

#include "GeneralStrategyHUD.h"
#include "GeneralStrategyPlayerController.h"
#include "GeneralStrategyPlayerState.h"
#include "GeneralStrategySpectatorPawn.h"
#include "GeneralStrategyCharacter.h"
#include "GeneralStrategyAIController.h"


AGeneralStrategyGameMode::AGeneralStrategyGameMode()
{
	HUDClass = AGeneralStrategyHUD::StaticClass();
	PlayerControllerClass = AGeneralStrategyPlayerController::StaticClass();
	DefaultPawnClass = AGeneralStrategySpectatorPawn::StaticClass();
}