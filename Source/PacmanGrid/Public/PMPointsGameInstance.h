// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PMPointsGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PACMANGRID_API UPMPointsGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere)
		int32 level;
	UPROPERTY(VisibleAnywhere)
		int32 base_points;
	UPROPERTY(VisibleAnywhere)
		int32 ghost_points;
	UPROPERTY(VisibleAnywhere)
		int32 power_points;



	virtual void Init() override;

public:
	UPROPERTY(VisibleAnywhere)
		int32 score;

	//used by ghosts to check house exit condition
	UPROPERTY(VisibleAnywhere)
		int32 partialScore;
	UPROPERTY(VisibleAnywhere)
		int32 lives;
	//functions to add points to score
	void add_powerPoints();

	void add_basePoints();

	void add_ghostPoints(int8);

	void reset_score();

	void reset_partialScore();

	//functions to add up lives

	void add_life();
	
	void remove_life();

	void reset_lives();

	int32 get_lives();

	
};
