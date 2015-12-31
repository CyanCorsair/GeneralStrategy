// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SpectatorPawn.h"
#include "GeneralStrategySpectatorPawn.generated.h"

/**
 * 
 */
UCLASS()
class GENERALSTRATEGY_API AGeneralStrategySpectatorPawn : public ASpectatorPawn
{
	GENERATED_BODY()

	public:

		/*===============================================================*/

		// Our basic constructor
		AGeneralStrategySpectatorPawn(const FObjectInitializer& ObjInit);

		// Camera component
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
			class UCameraComponent* CameraComponent;

		/*===============================================================*/

		/* PUBLIC VARIABLE DECLARATIONS */

		//--- ROTATION AND DISTANCE ---

		// Camera rotation around Z
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
			float CameraAngleZ;

		// Camera min distance
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
			float CameraMinDistance;

		// Camera max distance
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
			float CameraMaxDistance;

		// Default camera distance
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
			float DefaultCameraDistance;

		//--- PITCH CONTROLS ---

		// Camera max pitch
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
			float CameraMaxPitch;

		// Camera min pitch
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
			float CameraMinPitch;

		// Default camera pitch
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
			float DefaultCameraPitch;

		//--- SPEED SETTINGS ---

		// Camera zoom speed
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
			float CameraZoomSpeed;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
			float WheelZoomSpeed;

		// Camera rotation speed
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
			float CameraRotationSpeed;

		// Camera translation speed
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
			float CameraTranslationSpeed;

		//--- MISCELLANEOUS ---

		// Camera scroll bounds
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
			float CameraScrollBounds;

		// Should the camera be mobile?
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
			bool bIsMobile;

		/*===============================================================*/

	private:
		
		// Player input component constructor
		void SetupPlayerInputComponent(class UInputComponent* InputComponent);

		float CurrentCameraPitch,
			  CurrentCameraDistance,
			  CurrentCameraRotation;

		bool bWheelRotating;

		FVector2D CurrentMouseLocation;

		/*===============================================================*/

	/* FUNCTION DECLARATIONS */
	public:

		//--- WHEEL FUNCTIONS
		UFUNCTION()
			void WheelZoomIn();

		UFUNCTION()
			void WheelZoomOut();

		UFUNCTION()
			void WheelRotate(FVector2D MouseVelocity);

		//--- KEYBOARD FUNCTIONS
		UFUNCTION()
			void PanForward(float direction);

		UFUNCTION()
			void PanRight(float direction);

		UFUNCTION()
			void KeyZoom(float direction);

		UFUNCTION()
			void KeyRotate(float direction);

		//--- UTILITY FUNCTIONS
		UFUNCTION()
			void PositionCamera();

		UFUNCTION()
			FRotator GetIsolatedCameraYaw();

		// Needed override for key input
		UFUNCTION()
			virtual void Tick(float DeltaSeconds) override;
};
