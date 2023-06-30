// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GridPawn.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GridPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PACMANGRID_API AGridPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AGridPlayerController();
	void SetHorizontal(float Amount);
	void SetVertical(float Amount);
	void ClickOnGrid();

protected:
	virtual void BeginPlay() override; 
	virtual void SetupInputComponent() override;
	
};
