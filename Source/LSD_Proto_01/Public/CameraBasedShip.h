// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "Components/SceneComponent.h"
#include "CameraBasedShip.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LSD_PROTO_01_API UCameraBasedShip : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCameraBasedShip();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);

	UPROPERTY(EditAnywhere)
	USceneComponent* OurVisibleComponent;
	UPROPERTY(EditAnywhere)
	USceneComponent* ReticleClose;
	UPROPERTY(EditAnywhere)
	USceneComponent* ReticleFar;
	UPROPERTY(EditAnywhere, Category = "Movement")
	int inverted;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float translateSpeed;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float forwardVelocity;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float rotationSpeed;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float returnToSpeed;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float maxRotation;
	UPROPERTY(EditAnywhere, Category = "Camera")
	float XOffset;
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
