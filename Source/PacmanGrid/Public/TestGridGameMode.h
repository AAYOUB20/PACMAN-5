// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GridGenerator.h"
#include "GridPawn.h"
#include "Blinky.h"
#include "Inky.h"
#include "Pinky.h"
#include "PacmanPawn.h"
#include "GameFramework/GameMode.h"
#include "TestGridGameMode.generated.h"

class Blinky;

UENUM()
enum EState
{
	Scatter,
	Chase,
	Frightened
};
/**
 * 
 */
UCLASS()
class PACMANGRID_API ATestGridGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	// TSubclassOf is a template class that provides UClass type safety.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGridGenerator> GridGeneratorClass;

	// reference to a GameField object
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AGridGenerator* GField;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABlinky> BlinkyClass;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AInky> InkyClass;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<APinky> PinkyClass;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<APacmanPawn> PacmanClass;


	//refererence to the ghosts
	UPROPERTY(VisibleAnywhere)
	ABlinky* BlinkyPtr;

	UPROPERTY(VisibleAnywhere)
	AInky* InkyPtr;

	UPROPERTY(VisibleAnywhere)
	APinky* PinkyPtr;




	//reference to the pacman
	UPROPERTY(VisibleAnywhere)
	AGridPawn* PacmanPtr;

	UPROPERTY(VisibleAnywhere)
	TEnumAsByte<EState> CurrentState;

	int8 flash_count;

	bool bIsFlashing;

	FTimerHandle HouseTimer;


	ATestGridGameMode();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// functions of the state machine
	void FrightenedMode();
	void FlashingFrightenedMode();
	void ScatterMode();
	void ChaseMode();

	//time constants
	float PowerNode_time;
	float Fright_time;
	float Scatter_time_1;
	float Scatter_time_2;
	float Chase_time;

	

	//counting variables
	//the scatter mode is repeated only 4 times
	int16 Scatter_count;
	
	int8 EatenGhostCounter;

	//used to keep track of the state before frightened mode
	bool wasChaseMode;






private:
	// timer handles
	FTimerHandle FrightenedModeTimer;
	FTimerHandle ScatterModeTimer;
	FTimerHandle ChaseModeTimer;
	FTimerHandle FlashingTimer;



};
