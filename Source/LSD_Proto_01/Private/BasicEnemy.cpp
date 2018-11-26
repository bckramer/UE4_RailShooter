// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicEnemy.h"


// Sets default values
ABasicEnemy::ABasicEnemy(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	ParticleEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleEffect"));
	CollisionComp = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("BoxComp"));
	Muzzle = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Muzzle"));

	OurVisibleComponent->SetupAttachment(RootComponent);
	CollisionComp->SetupAttachment(RootComponent);
	ParticleEffect->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABasicEnemy::BeginPlay()
{
	Super::BeginPlay();
	CollisionComp->OnComponentHit.RemoveDynamic(this, &ABasicEnemy::OnHit);
	CollisionComp->OnComponentHit.AddDynamic(this, &ABasicEnemy::OnHit);
}

// Called every frame
void ABasicEnemy::Tick(float DeltaTime)
{

	time = time + (floatSpeed * DeltaTime);
	SetActorLocation(FVector(GetActorLocation().X - XChange, GetActorLocation().Y, GetActorLocation().Z + (ZChange * FMath::Sin(time))));
	//if (GEngine) {
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Z Change %f"), FMath::Sin(time)));
	//}
	Super::Tick(DeltaTime);	
	
}

void ABasicEnemy::Shoot() {
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AShip::StaticClass(), FoundActors);
	AShip* player = Cast<AShip>(FoundActors[0]);
	FVector const LaunchDir = GetActorLocation() - player->GetActorLocation();
	if (LaunchDir.X > 0.0f) {
		if (LaserClass != NULL) {
			FVector const MuzzleLocation = Muzzle->GetComponentLocation();
			FRotator MuzzleRotation = GetActorRotation();
			UWorld* const World = GetWorld();
			if (World)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				SpawnParams.Instigator = Instigator;
				// spawn the projectile at the muzzle
				ALaser* const Projectile = World->SpawnActor<ALaser>(LaserClass, MuzzleLocation, MuzzleRotation, SpawnParams);
				Projectile->ProjectileMovement->InitialSpeed = ProjectileVelocity;
				Projectile->ProjectileMovement->MaxSpeed = ProjectileVelocity;
				if (Projectile)
				{
					Projectile->InitVelocity(LaunchDir);
				}
			}
		}
	}
}

void ABasicEnemy::OnHit(UPrimitiveComponent * PrimitiveComponent1, AActor * Actor, 
						UPrimitiveComponent * PrimitiveComponent2, 
						FVector Vector, const FHitResult & HitResult) {
	if (Actor && (Actor != this) && PrimitiveComponent1)
	{
		//if (GEngine)
		//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Hit %f"), 1.0f));
		ParticleEffect->Activate();
		Health = Health - 10.0f;
		if (Health <= 0.0f) {
			Destroy();
		}
	}
}


