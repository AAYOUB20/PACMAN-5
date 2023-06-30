// Fill out your copyright notice in the Description page of Project Settings.


#include "PMPointsGameInstance.h"

void UPMPointsGameInstance::Init()
{  // valore dei punti
	base_points = 10;
	ghost_points = 200;
	power_points = 50;


	lives = 5;// numero di vita 

	score = 0;

}

void UPMPointsGameInstance::add_powerPoints()
{
	score += power_points;
	partialScore += power_points;

}

void UPMPointsGameInstance::add_basePoints()
{
	score += base_points;
	partialScore += base_points;
}

void UPMPointsGameInstance::add_ghostPoints(int8 EatenGhosts)
{
	switch (EatenGhosts) {
		case 1:
			score += ghost_points;
			break;
		case 2:
			score += ghost_points * 2;
			break;
		case 3:
			score += ghost_points * 4;
			break;
		case 4:
			score += ghost_points * 8;
			break;
	}
}


void UPMPointsGameInstance::reset_score()
{
	score = 0;

}

void UPMPointsGameInstance::reset_partialScore()
{
	partialScore = 0;
}

void UPMPointsGameInstance::add_life()
{
	lives += 1;
}

void UPMPointsGameInstance::remove_life()
{
	lives -= 1;
}

void UPMPointsGameInstance::reset_lives()
{
	lives = 5;
}

int32 UPMPointsGameInstance::get_lives()
{
	return lives;
}
