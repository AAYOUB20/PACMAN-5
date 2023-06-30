// Fill out your copyright notice in the Description page of Project Settings.


#include "Inky.h"
#include "TestGridGameMode.h"

AGridBaseNode* AInky::GetPlayerRelativeTarget()
{
	return Super::GetPlayerRelativeTarget();
}

AInky::AInky()
{
	CurrentGridCoords = FVector2D(5,26);
	ScatterTarget = nullptr;
	bIsWaiting = true;
	ghostExitPoints = 30;

}

void AInky::BeginPlay()
{
	Super::BeginPlay();
	FVector2D InkyScatter = FVector2D(1,25);
	ScatterTarget = *GridGenTMap.Find(InkyScatter);
	//SetNextNodeByDir(FVector(0, 0, 0), true);
	


}

void AInky::SetScatterTarget()
{

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Scatter target Function"));
	AGridBaseNode* PossibleNode = TheGridGen->GetClosestNodeFromMyCoordsToTargetCoords(this->GetLastNodeCoords(), ScatterTarget->GetGridPosition(), -(this->GetLastValidDirection()));

	const FVector Dimensions(60, 60, 20);
	//DrawDebugBox(GetWorld(), PossibleNode->GetTileCoordinates(), Dimensions, FColor::Red);

	if (PossibleNode)
	{
		this->SetNextNodeByDir(TheGridGen->GetThreeDOfTwoDVector(PossibleNode->GetGridPosition() - this->GetLastNodeCoords()), true);
	}
}

void AInky::SetChaseTarget()
{
	const AGridBaseNode* Target;
	FVector inputdir = GetPlayer()->GetLastValidDirection();
	FVector2D sum = FVector2D(2 * inputdir.X, 2 * inputdir.Y);
	
	if (inputdir == FVector(1, 0, 0))
		sum = FVector2D(2, -2);

	

	FVector2D CurrentICoords = GameMode->InkyPtr->GetCurrentGridCoords();
	FVector2D CurrentPCoords = GetPlayerRelativeTarget()->GetGridPosition();
	FVector2D PacmanProjection = FVector2D(CurrentPCoords.X + sum.X, CurrentPCoords.Y + sum.Y);
	FVector2D VectorPacmanBlinky = FVector2D((PacmanProjection.X - CurrentICoords.X) * 2, (PacmanProjection.Y - CurrentICoords.Y) * 2);

	FVector2D PossibleCoords = FVector2D(CurrentPCoords.X + sum.X, CurrentPCoords.Y + sum.Y);

	const float ClampedX = FMath::Clamp(PossibleCoords.X, 0, 32);
	const float ClampedY = FMath::Clamp(PossibleCoords.Y, 0, 27);

	Target = *(GridGenTMap.Find(FVector2D(ClampedX, ClampedY)));
	if (Target != nullptr) {

		AGridBaseNode* PossibleNode = TheGridGen->GetClosestNodeFromMyCoordsToTargetCoords(this->GetLastNodeCoords(), Target->GetGridPosition(), -(this->GetLastValidDirection()));

		const FVector Dimensions(60, 60, 20);
		DrawDebugBox(GetWorld(), PossibleNode->GetTileCoordinates(), Dimensions, FColor::Red);

		if (PossibleNode)
		{
			this->SetNextNodeByDir(TheGridGen->GetThreeDOfTwoDVector(PossibleNode->GetGridPosition() - this->GetLastNodeCoords()), true);
		}
	}

	
}

void AInky::SetEatenTarget() {

	const AGridBaseNode* Target = *GridGenTMap.Find(FVector2D(21, 13));


	//once outside, the ghost goes to the center of the ghost house
	if (CurrentGridCoords == FVector2D(21, 13))
	{
		SetTargetNode(*GridGenTMap.Find(FVector2D(19, 13)));

	}
	//once inside, the ghost is respawned and instantly kicked out of the ghost house
	else if (CurrentGridCoords == FVector2D(19, 12))
	{
		ResetOriginalColor();
		SetTargetNode(*GridGenTMap.Find(FVector2D(21, 13)));
		bIsEaten = false;
	}
	//if the ghost is eaten, it will go to the ghost house
	else {
		AGridBaseNode* PossibleNode = TheGridGen->GetClosestNodeFromMyCoordsToTargetCoords(this->GetLastNodeCoords(), Target->GetGridPosition(), -(this->GetLastValidDirection()));
		const FVector Dimensions(60, 60, 20);
		DrawDebugBox(GetWorld(), PossibleNode->GetTileCoordinates(), Dimensions, FColor::Red);
		if (PossibleNode)
		{
			this->SetNextNodeByDir(TheGridGen->GetThreeDOfTwoDVector(PossibleNode->GetGridPosition() - this->GetLastNodeCoords()), true);
		}
	}

}

void AInky::resetGhost()
{
	const FVector2D InkySpawn = FVector2D(19, 11);
	CurrentGridCoords = InkySpawn;
	LastNode = *(GridGenTMap.Find(InkySpawn));
	NextNode = *(GridGenTMap.Find(InkySpawn));
	SetTargetNode(*GridGenTMap.Find(InkySpawn));
	SetActorLocation(FVector(1850.f, 1150.f, 5.f));
	bIsEaten = false;
	bIsWaiting= true;
	bIsTimerStarted = false;
}

void AInky::ghostWait()
{
	// gli condizione per cui il ghost esce dall casa
	if (!(GameMode->PinkyPtr->getIsWaiting()))
		//once pinky has left, inky waits for the player to reach 30 points or until the time is up
		if (!bIsTimerStarted) {
			bIsTimerStarted = true;
			GetWorld()->GetTimerManager().SetTimer(GameMode->HouseTimer, this, &APhantomPawn::leaveHouse, 8.f, false);
		}

}
