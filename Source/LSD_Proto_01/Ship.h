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
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectGlobals.h"
#include "Laser.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
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
	virtual void SetCameraPosition();

	UPROPERTY(EditAnywhere)
	USceneComponent* OurVisibleComponent;
	UPROPERTY(EditAnywhere)
	USceneComponent* Muzzle;
	UPROPERTY(EditAnywhere)
	USceneComponent* ParticleEffectDamage;
	UPROPERTY(EditAnywhere)
	USceneComponent* ParticleEffectFire;
	UPROPERTY(EditAnywhere)
	USceneComponent* BoundaryAnchor;
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
	UPROPERTY(EditAnywhere, Category = "Boundary")
	float BoundaryHeight;
	UPROPERTY(EditAnywhere, Category = "Boundary")
	float BoundaryWidth;
	UPROPERTY(EditAnywhere, Category = "Boundary")
	float CameraBoundaryHeight;
	UPROPERTY(EditAnywhere, Category = "Boundary")
	float CameraBoundaryWidth;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Collision")
	UBoxComponent* CollisionComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float ProjectileVelocity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float Health;
	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ALaser> LaserClass;


	UFUNCTION(BlueprintCallable)
	void OnHit(UPrimitiveComponent * PrimitiveComponent1, AActor * Actor, UPrimitiveComponent * PrimitiveComponent2, FVector Vector, const FHitResult & HitResult);
	UFUNCTION(BlueprintCallable)
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
