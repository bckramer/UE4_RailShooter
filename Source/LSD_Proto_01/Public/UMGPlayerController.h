// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UMGPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class LSD_PROTO_01_API AUMGPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	
};
