// Fill out your copyright notice in the Description page of Project Settings.

#include "GeneralStrategy.h"
#include "GeneralStrategySpectatorPawn.h"

AGeneralStrategySpectatorPawn::AGeneralStrategySpectatorPawn(const FObjectInitializer& ObjInit)
	: Super(ObjInit)
{
	PrimaryActorTick.bCanEverTick = true;
	PlayerController = NULL;

	// Disable standard WASD movement bindings
	bAddDefaultMovementBindings = false;

	// Disable pitch, yaw and roll in controller's local space
	// We don't need these values since we're accelerating the camera separately
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	// Set up camera defaults
	DefaultCameraDistance = 3000.f;
	DefaultCameraPitch = 35.f;
	CameraAngleZ = 0.f;
	CameraScrollBounds = 25.f;

	CurrentCameraRotation = CameraAngleZ;
	CurrentCameraDistance = DefaultCameraDistance;
	CurrentCameraPitch = DefaultCameraPitch;

	bPawnRotating = false;
	bOldPawnRotating = false;
	bIsMobile = true;

	// Minimum and maximum camera values
	CameraMinDistance = 250.0f;
	CameraMaxDistance = 6000.0f;
	CameraMinPitch = 15.0f;
	CameraMaxPitch = 90.0f;

	// Camera speed per (multiplty by deltaTime)
	CameraRotationSpeed = 5.f;
	CameraZoomSpeed = 20.f;
	WheelZoomSpeed = 200.f;
	CameraTranslationSpeed = 15.f;

	// Set up the camera component and position it
	CameraComponent = ObjInit.CreateDefaultSubobject<UCameraComponent>(this, TEXT("DEFAULT CAMERA"));
	CameraComponent->AttachParent = this->GetRootComponent();
	//CameraComponent->bUsePawnControlRotation = false; // We don't want the pawn's rotation either
	PositionCamera();
}

// Set up our input component
void AGeneralStrategySpectatorPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	check(InputComponent);

	Super::SetupPlayerInputComponent(InputComponent);

	// Mouse commands
	InputComponent->BindAction("WheelZoomIn", IE_Pressed, this, &AGeneralStrategySpectatorPawn::WheelZoomIn);
	InputComponent->BindAction("WheelZoomOut", IE_Pressed, this, &AGeneralStrategySpectatorPawn::WheelZoomOut);

	// Key commands
	InputComponent->BindAxis("PanForward", this, &AGeneralStrategySpectatorPawn::PanForward);
	InputComponent->BindAxis("PanRight", this, &AGeneralStrategySpectatorPawn::PanRight);
	InputComponent->BindAxis("KeyZoom", this, &AGeneralStrategySpectatorPawn::KeyZoom);
	InputComponent->BindAxis("KeyRotate", this, &AGeneralStrategySpectatorPawn::KeyRotate);
}

void AGeneralStrategySpectatorPawn::WheelZoomIn()
{
	if (!bIsMobile || bPawnRotating) return;

	CurrentCameraDistance -= 0.65f * WheelZoomSpeed;
	CurrentCameraDistance = FMath::Clamp(CurrentCameraDistance, CameraMinDistance, CameraMaxDistance);

	PositionCamera();
}

void AGeneralStrategySpectatorPawn::WheelZoomOut()
{
	if (!bIsMobile || bPawnRotating) return;

	CurrentCameraDistance += 0.65f * WheelZoomSpeed;
	CurrentCameraDistance = FMath::Clamp(CurrentCameraDistance, CameraMinDistance, CameraMaxDistance);

	PositionCamera();
}

void AGeneralStrategySpectatorPawn::OnBeginRotation()
{
	bPawnRotating = true;
	PlayerController->bShowMouseCursor = false;
}

void AGeneralStrategySpectatorPawn::OnEndRotation()
{
	bPawnRotating = false;
	PlayerController->bShowMouseCursor = true;
}

void AGeneralStrategySpectatorPawn::PawnRotate(FVector2D MouseVelocity)
{
	if (!bIsMobile) return;

	FRotator NewRotation(0.f, 0.f, 0.f);
	CurrentCameraRotation += (MouseVelocity.X * CameraRotationSpeed);
	CurrentPawnPitch += (MouseVelocity.Y * CameraRotationSpeed);

	NewRotation.Yaw = CurrentCameraRotation;
	NewRotation.Pitch = CurrentPawnPitch;

	SetActorRotation(NewRotation);
}

void AGeneralStrategySpectatorPawn::PanForward(float direction)
{
	if (!bIsMobile || bPawnRotating) return;

	float AmountToMove = direction * CameraTranslationSpeed;
	FVector DeltaMovement = AmountToMove * GetIsolatedCameraYaw().Vector();
	FVector NewLocation = GetActorLocation() + DeltaMovement;

	SetActorLocation(NewLocation);
}

void AGeneralStrategySpectatorPawn::PanRight(float direction)
{
	if (!bIsMobile || bPawnRotating) return;

	float AmountToMove = direction * CameraTranslationSpeed;
	FVector DeltaMovement = AmountToMove * (FRotator(0.f, 90.f, 0.f) + GetIsolatedCameraYaw()).Vector();
	FVector NewLocation = GetActorLocation() + DeltaMovement;

	SetActorLocation(NewLocation);
}

void AGeneralStrategySpectatorPawn::KeyZoom(float direction)
{
	if (!bIsMobile || bPawnRotating) return;

	float AmountToMove = direction * CameraZoomSpeed;
	CurrentCameraDistance += AmountToMove;
	CurrentCameraDistance = FMath::Clamp(CurrentCameraDistance, CameraMinDistance, CameraMaxDistance);

	PositionCamera();
}

void AGeneralStrategySpectatorPawn::KeyRotate(float direction)
{
	if (!bIsMobile || bPawnRotating) return;

	FRotator NewRotation(0.f, 0.f, 0.f);
	CurrentCameraRotation += direction * CameraRotationSpeed;

	NewRotation.Yaw = CurrentCameraRotation;
	NewRotation.Pitch = CurrentPawnPitch;

	SetActorRotation(NewRotation);
}

void AGeneralStrategySpectatorPawn::PositionCamera()
{
	FVector newLocation(0.f, 0.f, 0.f);
	FRotator newRotation(0.f, 0.f, 0.f);

	float sinCameraZAngle = FMath::Sin(FMath::DegreesToRadians(CameraAngleZ));
	float cosCameraZAngle = FMath::Cos(FMath::DegreesToRadians(CameraAngleZ));

	float sinCameraHeightAngle = FMath::Sin(FMath::DegreesToRadians(CurrentCameraPitch));
	float cosCameraHeightAngle = FMath::Cos(FMath::DegreesToRadians(CurrentCameraPitch));

	newLocation.X = cosCameraZAngle * cosCameraHeightAngle * CurrentCameraDistance;
	newLocation.Y = sinCameraZAngle * cosCameraHeightAngle * CurrentCameraDistance;
	newLocation.Z = sinCameraHeightAngle * CurrentCameraDistance;

	newRotation = (FVector(0.f, 90.f, 0.f) - newLocation).Rotation();
	newRotation.Yaw = 180.f;

	// new camera location and rotation
	CameraComponent->SetRelativeLocation(newLocation);
	CameraComponent->SetRelativeRotation(newRotation);
}

FRotator AGeneralStrategySpectatorPawn::GetIsolatedCameraYaw()
{
	// FRotator containing only yaw
	return FRotator(0.0f, CameraComponent->ComponentToWorld.Rotator().Yaw, 0.0f);
}

void AGeneralStrategySpectatorPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (PlayerController == NULL) PlayerController = Cast<APlayerController>(GetController());

	PlayerController->GetViewportSize(Width, Height);
	PlayerController->GetMousePosition(MouseLocation.X, MouseLocation.Y);
	PlayerController->GetInputMouseDelta(MouseVelocity.X, MouseVelocity.Y);

	ViewportSize.X = Width * 1.f;
	ViewportSize.Y = Height * 1.f;

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Mouse: x: %f, y: %f; Viewport: Width: %f, Height: %f"), MouseLocation.X, MouseLocation.Y, ViewportSize.X, ViewportSize.Y));

	if (MouseLocation.X <= CameraScrollBounds && MouseLocation.X >= 0)
	{
		PanRight(-1.f);
	}

	if (MouseLocation.X >= (ViewportSize.X - CameraScrollBounds) && MouseLocation.X <= ViewportSize.X)
	{
		PanRight(1.f);
	}

	if (MouseLocation.Y <= CameraScrollBounds && MouseLocation.Y >= 0)
	{
		PanForward(1.f);
	}

	if (MouseLocation.Y >= (ViewportSize.Y - CameraScrollBounds) && MouseLocation.Y <= ViewportSize.Y)
	{
		PanForward(-1.f);
	}

	if (bPawnRotating)
	{
		PawnRotate(MouseVelocity);
	}
}