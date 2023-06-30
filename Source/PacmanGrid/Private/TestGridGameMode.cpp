// Fill out your copyright notice in the Description page of Project Settings.


#include "TestGridGameMode.h"
#include "PacmanWidget.h"


ATestGridGameMode::ATestGridGameMode()
{
	PowerNode_time = 6.0f;
	Scatter_time_1 = 7.0f;
	Scatter_time_2 = 5.0f;
	Chase_time = 20.0f;
	Fright_time = 3.0f;
	//starting in scatter mode
	wasChaseMode = false;
}

void ATestGridGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	// con questa posizione la tile di coordinate griglia (0,0) ha come
	// coordinate nello spazio dello spigolo inferiore sinistro (0,0) 
	// 
	// es. coordinate nello spazio della tile di coordinate di griglia (0, 0) 
	// 
	// (100,0) -------------- (100,100)
    //         |            |
	//		   |            |
	//         |  (50, 50)  |
	//         |            |
	//         |            |
	//  (0,0)  -------------- (0, 100)
	//

	FVector GridPos(50.0f, 50.0f, 0.0f);
	// N.B. tutte le funzioni andrebbero normalizzate se la posizione
	// della griglia non fosse più questa ma una qualsiasi nello spazio tridimensionale
	if (GridGeneratorClass != nullptr)
	{
		// spawn della griglia
		GField = GetWorld()->SpawnActor<AGridGenerator>(GridGeneratorClass, GridPos, FRotationMatrix::MakeFromX(FVector(0, 0, 0)).Rotator());
	};

	BlinkyPtr = GetWorld()->SpawnActor<ABlinky>(BlinkyClass, FVector((100 * 21) + 50, (100 * 13) + 50, 5.0f), FRotator(0, 0, 0));
	InkyPtr = GetWorld()->SpawnActor<AInky>(InkyClass, FVector((100 * 18) + 50, (100 * 11) + 50, 5.0f), FRotator(0, 0, 0));
	PinkyPtr = GetWorld()->SpawnActor<APinky>(PinkyClass, FVector((100 * 18) + 50, (100 * 13) + 50, 5.0f), FRotator(0, 0, 0));
	PacmanPtr = Cast<APacmanPawn>(UGameplayStatics::GetActorOfClass(GetWorld(), PacmanClass));
	CurrentState=EState::Scatter;
	GetWorld()->GetTimerManager().SetTimer(ScatterModeTimer, this, &ATestGridGameMode::ScatterMode, 3.0f , false);
	PinkyPtr->ghostWait();

}

void ATestGridGameMode::FrightenedMode()
{
	//must pause the timer of the previous state
	if (wasChaseMode) {
		GetWorld()->GetTimerManager().PauseTimer(ChaseModeTimer);
	}
	else {
		GetWorld()->GetTimerManager().PauseTimer(ScatterModeTimer);
	}
	BlinkyPtr->flipDirection();
	InkyPtr->flipDirection();
	PinkyPtr->flipDirection();
	//updating the state of the game
	CurrentState=EState::Frightened;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Frightened Mode"));
	bIsFlashing = false;
	EatenGhostCounter = 0;

	BlinkyPtr->VisibleBlue();
	InkyPtr->VisibleBlue();
	PinkyPtr->VisibleBlue();
	//setting the timer for the end of the frightened mode
	
	GetWorld()->GetTimerManager().SetTimer(FrightenedModeTimer, this, &ATestGridGameMode::FlashingFrightenedMode,Fright_time , false);

}

void ATestGridGameMode::FlashingFrightenedMode()
{
	bIsFlashing = true;
	flash_count = 0;
	BlinkyPtr->VisibleWhite();
	InkyPtr->VisibleWhite();
	PinkyPtr->VisibleWhite();
	//different states to retourn to
	if (wasChaseMode) {
		GetWorld()->GetTimerManager().UnPauseTimer(ChaseModeTimer);
		ChaseMode();
	}
	else {
		GetWorld()->GetTimerManager().UnPauseTimer(ScatterModeTimer);
		ScatterMode();
	}
}



void ATestGridGameMode::ScatterMode()
{
	//Debug message
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Scatter Mode"));
	CurrentState = EState::Scatter;
	Scatter_count += 1;
	wasChaseMode = false;


	//signaling ghost pawn to revert direction
	
	BlinkyPtr->flipDirection();
	InkyPtr->flipDirection();
	//PinkyPtr->flipDirection();


	//the scatter time changes after the first 2 scatter modes
	if (Scatter_count < 3)
		GetWorld()->GetTimerManager().SetTimer(ScatterModeTimer, this, &ATestGridGameMode::ChaseMode, Scatter_time_1, false);
	else if (Scatter_count == 3 || Scatter_count == 4)
		GetWorld()->GetTimerManager().SetTimer(ScatterModeTimer, this, &ATestGridGameMode::ChaseMode, Scatter_time_2, false);
}

//to be implemented
void ATestGridGameMode::ChaseMode()
{//Debug message

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Chase Mode"));
	CurrentState = EState::Chase;
	wasChaseMode = true;
	//signaling ghost pawn to change their behaviour
	BlinkyPtr->flipDirection();
	InkyPtr->flipDirection();
	PinkyPtr->flipDirection();
	//setting the timer for the end of the chase mode
	GetWorld()->GetTimerManager().SetTimer(ChaseModeTimer, this, &ATestGridGameMode::ScatterMode, Chase_time, false);
}




