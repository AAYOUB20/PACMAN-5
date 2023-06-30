// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PMPointsGameInstance.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "PacmanWidget.generated.h"

/**
 * 
 */
UCLASS()
class PACMANGRID_API UPacmanWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void DisplayScore(int32 score);
	void DisplayLives(int8 lives);
	void DisplayGameOver(FString gameOver);

protected:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* ScoreLabel;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* LivesLabel;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* GameOverLabel;

	// get reference to game instance
	UPROPERTY(VisibleAnywhere)
		UPMPointsGameInstance* PointsGameInstance;

	void NativeConstruct() override;

};
	
