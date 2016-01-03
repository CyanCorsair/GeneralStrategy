// Fill out your copyright notice in the Description page of Project Settings.

#include "GeneralStrategy.h"
#include "GeneralStrategyCharacter.h"


// Sets default values
AGeneralStrategyCharacter::AGeneralStrategyCharacter(const FObjectInitializer& ObjInit)
	: Super(ObjInit)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGeneralStrategyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGeneralStrategyCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

// Called to bind functionality to input
void AGeneralStrategyCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
}

