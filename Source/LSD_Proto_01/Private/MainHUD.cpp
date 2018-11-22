// Fill out your copyright notice in the Description page of Project Settings.

#include "MainHUD.h"


AMainHUD::AMainHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshairTexObj(TEXT("Texture2D'/Game/StarterContent/Crosshairs/crosshair042.crosshair042'"));
	CrosshairTexture = CrosshairTexObj.Object;

}


void AMainHUD::DrawHUD()
{
	Super::DrawHUD();
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AShip::StaticClass(), FoundActors);
	AShip* player = Cast<AShip>(FoundActors[0]);
	USceneComponent* ReticleClose = player->ReticleClose;
	USceneComponent* ReticleFar = player->ReticleFar;

	if (CrosshairTexture)
	{
		// Find the center of our canvas.
		FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
		float yPos = ReticleClose->GetComponentLocation().X / ReticleClose->GetComponentLocation().Z;
		float xPos = ReticleClose->GetComponentLocation().Y / ReticleClose->GetComponentLocation().Z;
		FVector location = Canvas->Project(ReticleClose->GetComponentLocation());
		FVector location1 = Canvas->Project(ReticleFar->GetComponentLocation());
		FVector2D CrossHairDrawPosition(location.X - (CrosshairTexture->GetSurfaceWidth() * 0.5), location.Y - (CrosshairTexture->GetSurfaceHeight() * 0.5f));
		//if (GEngine)
		//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Location.X %f"), location.X));

		// Offset by half of the texture's dimensions so that the center of the texture aligns with the center of the Canvas.

		// Draw the crosshair at the centerpoint.
		FVector2D CrossHairDrawPosition1(location1.X - (CrosshairTexture->GetSurfaceWidth() * 0.5), location1.Y - (CrosshairTexture->GetSurfaceHeight() * 0.5f));
		FCanvasTileItem TileItem(CrossHairDrawPosition, CrosshairTexture->Resource, FLinearColor::White);
		TileItem.BlendMode = SE_BLEND_Translucent;
		Canvas->DrawItem(TileItem);

		FCanvasTileItem TileItem1(CrossHairDrawPosition1, CrosshairTexture->Resource, FLinearColor::White);
		TileItem1.BlendMode = SE_BLEND_Translucent;
		Canvas->DrawItem(TileItem1);
	}
}


