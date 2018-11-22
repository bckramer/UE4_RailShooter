// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Components/SplineComponent.h"
#include "Laser.h"
#include "EngineGlobals.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Engine.h"
#include <math.h>
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "BasicEnemy.generated.h"

UCLASS()
class LSD_PROTO_01_API ABasicEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasicEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;	
	float time = 0;
	UPROPERTY(EditAnywhere)
	USceneComponent* OurVisibleComponent;
	UPROPERTY(EditAnywhere)
	USceneComponent* ParticleEffect;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Projectile")
	UBoxComponent* CollisionComp;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Path)
	//USplineComponent* SplinePath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ALaser> LaserClass;
	UPROPERTY(EditAnywhere, Category = Health)
	float Health;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float XChange;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float ZChange;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float floatSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float ProjectileVelocity;
	UFUNCTION(BlueprintCallable)
	void OnHit(UPrimitiveComponent * PrimitiveComponent1, AActor * Actor, UPrimitiveComponent * PrimitiveComponent2, FVector Vector, const FHitResult & HitResult);
	UFUNCTION(BlueprintCallable)
	void Shoot();
	ABasicEnemy(const FObjectInitializer& ObjectInitializer);
};
