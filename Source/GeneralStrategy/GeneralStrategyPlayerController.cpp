// Fill out your copyright notice in the Description page of Project Settings.

#include "GeneralStrategy.h"
#include "GeneralStrategyPlayerController.h"

AGeneralStrategyPlayerController::AGeneralStrategyPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;

	FVector2D MousePosition(0.f, 0.f);
	FVector2D MouseVelocity(0.f, 0.f);
}

void AGeneralStrategyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	check(InputComponent);

	InputComponent->BindAction("LeftClick", IE_Pressed, this, &AGeneralStrategyPlayerController::LeftMousePressed);
	InputComponent->BindAction("LeftClick", IE_Released, this, &AGeneralStrategyPlayerController::LeftMouseReleased);
	
	InputComponent->BindAction("RightClick", IE_Pressed, this, &AGeneralStrategyPlayerController::RightMousePressed);
	InputComponent->BindAction("RightClick", IE_Released, this, &AGeneralStrategyPlayerController::RightMouseReleased);
}

void AGeneralStrategyPlayerController::AddToSelection(AActor* Selected)
{
	if (!CurrentSelection.Contains(Selected))
	{
		CurrentSelection.Add(Selected);
	}

	// Check contents for debug
	for (int8 i = 0; i != CurrentSelection.Num(); ++i)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Actors in selection: %s."), *CurrentSelection[i]->GetName()));
	}
}

void AGeneralStrategyPlayerController::LeftMousePressed()
{
	FHitResult TraceResult(ForceInit);
	GetHitResultUnderCursor(ECollisionChannel::ECC_WorldDynamic, false, TraceResult);

	if (TraceResult.GetActor() != nullptr)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Trace Actor %s."), *TraceResult.GetActor()->GetName()));
		AActor* Result = TraceResult.GetActor();
		AddToSelection(Result);
	}
	else
	{
		CurrentSelection.Empty();
	}
}

void AGeneralStrategyPlayerController::LeftMouseReleased()
{

}

void AGeneralStrategyPlayerController::RightMousePressed()
{
	CurrentPawn = Cast<AGeneralStrategySpectatorPawn>(GetPawn());
}

void AGeneralStrategyPlayerController::RightMouseReleased()
{
	if (CurrentSelection.Num() > 0 && !CurrentPawn->bPawnRotating)
	{
		FVector NewLocation(0.f, 0.f, 0.f);
		for (auto& Unit : CurrentSelection)
		{
			Unit->SetActorLocation(NewLocation);
		}
	}

	CurrentPawn->OnEndRotation();
}

void AGeneralStrategyPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	GetMousePosition(MousePosition.X, MousePosition.Y);
	GetInputMouseDelta(MouseVelocity.X, MouseVelocity.Y);

	if (IsInputKeyDown(EKeys::RightMouseButton) && (MouseVelocity.X > 0 || MouseVelocity.Y > 0)) CurrentPawn->OnBeginRotation();
}