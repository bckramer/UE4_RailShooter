// Fill out your copyright notice in the Description page of Project Settings.

#include "Ship.h"
#include "LSD_PROTO_01.h"
#include "Camera/CameraComponent.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"
#include "GameFramework/SpringArmComponent.h"
#include <iostream>


// Sets default values
AShip::AShip()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Set this pawn to be controlled by the lowest-numbered player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Create a dummy root component we can attach things to.
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	// Create a camera and a visible object
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	ReticleClose = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ReticleClose"));
	ReticleFar = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ReticleFar"));

	OurCameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	OurCameraSpringArm->SetupAttachment(RootComponent);
	OurCameraSpringArm->TargetArmLength = 400.f;
	OurCameraSpringArm->bEnableCameraLag = true;
	OurCameraSpringArm->CameraLagSpeed = 3.0f;

	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
	OurCamera->SetupAttachment(OurCameraSpringArm, USpringArmComponent::SocketName);
	OurVisibleComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AShip::BeginPlay()
{
	Super::BeginPlay();
	PrevRotation = FRotator(270.0f, 0.0f, 0.0f);

}

// Called every frame
void AShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Handle movement based on our "MoveX" and "MoveY" axes
	{
		CurrentVelocity.X = forwardVelocity;
		const FVector LocalMove = FVector(forwardVelocity * DeltaTime, 0.f, 0.f);
		AddActorLocalOffset(LocalMove, true);
		if (!fieldMode) {
			OurCameraSpringArm->bInheritYaw = 0;
			OurCameraSpringArm->bInheritPitch = 0;
			OurCameraSpringArm->bInheritRoll = 0;
			OurCameraSpringArm->SetWorldLocation(FVector(GetActorLocation().X - XOffset, StartLocation.Y, StartLocation.Z), false, 0);
		}
		else {
			bMaxRotation = false;
			//OurCameraSpringArm->bInheritYaw = 1;
			OurCameraSpringArm->bAbsoluteRotation = 0;
			//OurCameraSpringArm->SetWorldLocation(FVector(GetActorLocation().X - XOffset, GetActorLocation().Y, GetActorLocation().Z), false, 0);
		}
		//SetActorLocation(NewLocation);
		if (currentYInput == 0 && currentZInput == 0) {
			//AddActorLocalRotation(DeltaRotation);
			SetActorRotation(FMath::RInterpTo(GetActorRotation(), FRotator(CurrentRotation.Pitch, CurrentRotation.Yaw, CurrentRotation.Roll), DeltaTime, returnToSpeed));
		} else {
			SetActorRotation(FMath::RInterpTo(GetActorRotation(), FRotator(CurrentRotation.Pitch, CurrentRotation.Yaw, CurrentRotation.Roll), DeltaTime, rotationSpeed));
		}
	}

}

// Called to bind functionality to input
void AShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Respond when our "Grow" key is pressed or released.
	InputComponent->BindAction("Grow", IE_Pressed, this, &AShip::StartGrowing);
	InputComponent->BindAction("Grow", IE_Released, this, &AShip::StopGrowing);

	// Respond every frame to the values of our two movement axes, "MoveX" and "MoveY".
	InputComponent->BindAxis("MoveZ", this, &AShip::Move_ZAxis);
	InputComponent->BindAxis("MoveY", this, &AShip::Move_YAxis);

}

void AShip::Move_ZAxis(float AxisValue)
{

	// Move at 100 units per second forward or backward
	float rotation = rotationSpeed * AxisValue;
	currentZInput = AxisValue;
	CurrentVelocity.Z = inverted * (FMath::Clamp(AxisValue, -10.0f, 10.0f) * translateSpeed);
	if (GetActorRotation().Pitch < maxRotation && GetActorRotation().Pitch > -maxRotation) {
		CurrentRotation.Pitch = GetActorRotation().Pitch + (inverted * rotation);
	}
	else {
		CurrentRotation.Pitch = GetActorRotation().Pitch;
	}
	if (AxisValue == 0.0f) {
		CurrentRotation.Pitch = 0.0f;
	}
}

void AShip::Move_YAxis(float AxisValue)
{
	// Move at 100 units per second right or left
	float rotation = rotationSpeed * AxisValue;
	currentYInput = AxisValue;
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * translateSpeed;
	if (GetActorRotation().Roll < maxRotation && GetActorRotation().Roll > -maxRotation) {
		CurrentRotation.Roll = GetActorRotation().Roll + rotation;
	}
	else {
		CurrentRotation.Roll = GetActorRotation().Roll;
	}
	if (bMaxRotation) {
		if (GetActorRotation().Yaw < maxRotation && GetActorRotation().Yaw > -maxRotation) {
			CurrentRotation.Yaw = GetActorRotation().Yaw + rotation;
		}
		else {
			CurrentRotation.Yaw = GetActorRotation().Yaw;
		}
	}
	else {
		CurrentRotation.Yaw = GetActorRotation().Yaw + rotation;
	}
	if (AxisValue == 0.0f) {
		CurrentRotation.Roll = 0.0f;
	}
	if (AxisValue == 0.0f && !fieldMode) {
		CurrentRotation.Yaw = 0.0f;
	}
}

void AShip::StartGrowing()
{
	bGrowing = true;
}

void AShip::StopGrowing()
{
	bGrowing = false;
}

