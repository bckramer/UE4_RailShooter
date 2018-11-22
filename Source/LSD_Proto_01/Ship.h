// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "GameFramework/SpringArmComponent.h"
#include "Laser.h"
#include <math.h>
#include "Ship.generated.h"

UCLASS()
class LSD_PROTO_01_API AShip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AShip();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	USceneComponent* OurVisibleComponent;
	UPROPERTY(EditAnywhere)
	USceneComponent* ReticleClose;
	UPROPERTY(EditAnywhere)
	USceneComponent* ReticleFar;
	UPROPERTY(EditAnywhere)
	USpringArmComponent* OurCameraSpringArm;
	UPROPERTY(EditAnywhere)
	USceneComponent* OurCamera;
	UPROPERTY(EditAnywhere, Category = "Movement")
	int inverted = 1;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float translateSpeed = 800.0f;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float forwardVelocity = 20.0f;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float rotationSpeed = 10.0f;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float returnToSpeed = 5.0f;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float maxRotation = 35.0f;
	UPROPERTY(EditAnywhere, Category = "Movement")
	bool fieldMode = false;
	UPROPERTY(EditAnywhere, Category = "Movement")
	bool bMaxRotation = true;
	UPROPERTY(EditAnywhere, Category = "Camera")
	float XOffset = 150.0f;
	UPROPERTY(EditAnywhere, Category = "Camera")
	float CameraBoundHeight = 200.0f;
	UPROPERTY(EditAnywhere, Category = "Camera")
	float CameraBoundWidth = 200.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float ProjectileVelocity;
	UPROPERTY(EditAnywhere, Category = "Camera")
	FVector StartLocation = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().X);
	/** Offset From the Ship */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;
	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ALaser> LaserClass;

	//handles firing
	UFUNCTION()
	void OnFire();

	float currentYInput;
	float currentZInput;

	//Input functions
	void Move_ZAxis(float AxisValue);
	void Move_YAxis(float AxisValue);
	void StartGrowing();
	void StopGrowing();

	//Input variables
	FVector CurrentVelocity;
	FRotator CurrentRotation;
	FRotator PrevRotation;
	bool bGrowing;

};
