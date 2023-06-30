// Fill out your copyright notice in the Description page of Project Settings.


#include "PacmanWidget.h"

void UPacmanWidget::NativeConstruct()
{
	Super::NativeConstruct();
	PointsGameInstance = Cast<UPMPointsGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	DisplayScore(0);
	DisplayLives(3);
	DisplayGameOver("");
}

void UPacmanWidget::DisplayScore(int32 score)
{
		ScoreLabel->SetText(FText::AsNumber(score));
}

void UPacmanWidget::DisplayLives(int8 lives)
{
		LivesLabel->SetText(FText::AsNumber(lives));
}

void UPacmanWidget::DisplayGameOver(FString gameOver)
{
		GameOverLabel->SetText(FText::FromString(gameOver));
}

