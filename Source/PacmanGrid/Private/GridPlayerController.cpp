// Fill out your copyright notice in the Description page of Project Settings.


#include "GridPlayerController.h"
AGridPlayerController::AGridPlayerController()
{
	bShowMouseCursor = true;
}

void AGridPlayerController::BeginPlay()
{
}

void AGridPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	//Bind grid movement Actions here
	InputComponent->BindAxis(TEXT("MoveForward"), this, &AGridPlayerController::SetVertical);
	InputComponent->BindAxis(TEXT("MoveRight"), this, &AGridPlayerController::SetHorizontal);
	// bind the OnClick function to InputComponent for testing purpose
	InputComponent->BindAction("Click", IE_Pressed, this, &AGridPlayerController::ClickOnGrid);
}

void AGridPlayerController::SetHorizontal(float Amount)
{
	const auto P = Cast<AGridPawn>(GetPawn());
	if (P)
	{
		P->SetHorizontalInput(Amount);
	}

}

void AGridPlayerController::SetVertical(float Amount)
{
	const auto P = Cast<AGridPawn>(GetPawn());
	if (P)
	{
		P->SetVerticalInput(Amount);
	}
}

void AGridPlayerController::ClickOnGrid()
{
	const auto P = Cast<AGridPawn>(GetPawn());
	if (P)
	{
		P->OnClick();
	}
}
