// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicEnemyCharacter.h"


// Sets default values
ABasicEnemyCharacter::ABasicEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABasicEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasicEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasicEnemyCharacter::Shoot() {
	if (LaserClass != NULL) {
		FVector const MuzzleLocation = GetActorLocation() + FTransform(GetActorLocation()).TransformVector(MuzzleOffset);
		FRotator MuzzleRotation = GetActorRotation();
		UWorld* const World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;
			// spawn the projectile at the muzzle
			ALaser* const Projectile = World->SpawnActor<ALaser>(LaserClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				// find launch direction
				FVector const LaunchDir = MuzzleRotation.Vector();
				Projectile->InitVelocity(LaunchDir);
			}
		}
	}
}
