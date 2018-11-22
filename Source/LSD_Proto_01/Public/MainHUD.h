// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Runtime/Engine/Classes/Engine/Canvas.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Ship.h"
#include "MainHUD.generated.h"

/**
 * 
 */
UCLASS()
class LSD_PROTO_01_API AMainHUD : public AHUD
{
	GENERATED_BODY()
	AMainHUD(const FObjectInitializer& ObjectInitializer);

public:
	// Primary draw call for the HUD.
	virtual void DrawHUD() override;

protected:
	// This will be drawn at the center of the screen.
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* CrosshairTexture;

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* CrosshairTexture1;
};
