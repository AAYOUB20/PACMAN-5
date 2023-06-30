// Fill out your copyright notice in the Description page of Project Settings.


#include "Pinky.h"
#include "TestGridGameMode.h"

AGridBaseNode* APinky::GetPlayerRelativeTarget()
{
	return Super::GetPlayerRelativeTarget();
}

APinky::APinky()
{
	CurrentGridCoords = FVector2D(18, 13);// Imposta la posizione iniziale di pinky
	ScatterTarget = nullptr;
	bIsWaiting = true;
	ghostExitPoints = 0;
}

void APinky::BeginPlay()
{
	Super::BeginPlay();
	FVector2D PinkyScatter = FVector2D(32, 2);
	ScatterTarget = *GridGenTMap.Find(PinkyScatter);



}

void APinky::SetScatterTarget()
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

//Chase logic
void APinky::SetChaseTarget()
{
	const AGridBaseNode* Target;
	FVector inputdir = GetPlayer()->GetLastValidDirection();
	FVector2D sum = FVector2D(4 * inputdir.X, 4 * inputdir.Y);

	if (inputdir == FVector(1, 0, 0))
		sum = FVector2D(4, -4);
	FVector2D CurrentPCoords = GetPlayerRelativeTarget()->GetGridPosition();
	FVector2D PossibleCoords= FVector2D(CurrentPCoords.X + sum.X, CurrentPCoords.Y+ sum.Y);

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

void APinky::SetEatenTarget() {

	const AGridBaseNode* Target = *GridGenTMap.Find(FVector2D(21, 13));


	if (CurrentGridCoords == FVector2D(21, 13))
	{
		SetTargetNode(*GridGenTMap.Find(FVector2D(18, 13)));

	}
	else if (CurrentGridCoords == FVector2D(18, 13))
	{
		ResetOriginalColor();
		SetTargetNode(*GridGenTMap.Find(FVector2D(21, 13)));
		bIsEaten = false;
	}
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

void APinky::resetGhost()
{
	const FVector2D PinkySpawn = FVector2D(18, 13);
	CurrentGridCoords = PinkySpawn;
	LastNode = *(GridGenTMap.Find(PinkySpawn));
	NextNode = *(GridGenTMap.Find(PinkySpawn));
	SetTargetNode(*GridGenTMap.Find(PinkySpawn));
	SetActorLocation(FVector(1850.f, 1350.f, 5.f));
	bIsEaten = false;
	bIsWaiting = true;
	bIsTimerStarted = false;
}

void APinky::ghostWait()
{
	
	if (!bIsTimerStarted) {
		bIsTimerStarted = true;
		GetWorld()->GetTimerManager().SetTimer(GameMode->HouseTimer, this, &APinky::leaveHouse, 8.f, false);
	}
	if (PointsGameInstance->partialScore >= ghostExitPoints) 
		leaveHouse();
}
// gli condizione per cui il ghost esce dall casa