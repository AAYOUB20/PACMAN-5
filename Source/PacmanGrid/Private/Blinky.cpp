// Fill out your copyright notice in the Description page of Project Settings.


#include "Blinky.h"
#include "TestGridGameMode.h"

AGridBaseNode* ABlinky::GetPlayerRelativeTarget()
{
	return Super::GetPlayerRelativeTarget();
}

ABlinky::ABlinky()
{
	CurrentGridCoords = FVector2D(21,13);
	ScatterTarget = nullptr;
	bIsWaiting = false;
}

void ABlinky::BeginPlay()
{
	Super::BeginPlay();
	FVector2D BlinkyScatter = FVector2D(32, 25);
	ScatterTarget = *GridGenTMap.Find(BlinkyScatter);
	//SetNextNodeByDir(FVector(0, 0, 0), true);
}

void ABlinky::SetScatterTarget()
{
	
	AGridBaseNode* PossibleNode = TheGridGen->GetClosestNodeFromMyCoordsToTargetCoords(this->GetLastNodeCoords(), ScatterTarget->GetGridPosition(), -(this->GetLastValidDirection()));

	const FVector Dimensions(60, 60, 20);
	DrawDebugBox(GetWorld(), PossibleNode->GetTileCoordinates(), Dimensions, FColor::Red);

	if (PossibleNode)
	{
		this->SetNextNodeByDir(TheGridGen->GetThreeDOfTwoDVector(PossibleNode->GetGridPosition() - this->GetLastNodeCoords()), true);
	}
}

void ABlinky::SetChaseTarget()
{
	const AGridBaseNode* Target = GetPlayerRelativeTarget();
	if (!Target)
	{
		Target = GetPlayer()->GetLastNode();
	}

	AGridBaseNode* PossibleNode = TheGridGen->GetClosestNodeFromMyCoordsToTargetCoords(this->GetLastNodeCoords(), Target->GetGridPosition(), -(this->GetLastValidDirection()));

	const FVector Dimensions(60, 60, 20);
	DrawDebugBox(GetWorld(), PossibleNode->GetTileCoordinates(), Dimensions, FColor::Red);

	if (PossibleNode)
	{
		this->SetNextNodeByDir(TheGridGen->GetThreeDOfTwoDVector(PossibleNode->GetGridPosition() - this->GetLastNodeCoords()), true);
	}
}
//nell caso che il fantasma viene mangiata deve ritornare al casa (19, 13) per riavviela poi si esce al  (21, 13)
void ABlinky::SetEatenTarget() {
	
	const AGridBaseNode* Target = *GridGenTMap.Find(FVector2D(21,13));

	if (CurrentGridCoords == FVector2D(21, 13))
	{			
		SetTargetNode(*GridGenTMap.Find(FVector2D(19, 13)));
		
	}

	else if (CurrentGridCoords == FVector2D(19, 13))
	{
		ResetOriginalColor();
		SetTargetNode(*GridGenTMap.Find(FVector2D(21, 13)));
		bIsEaten = false;
	}
	else {
		AGridBaseNode* PossibleNode = TheGridGen->GetClosestNodeFromMyCoordsToTargetCoords(this->GetLastNodeCoords(), Target->GetGridPosition(), -(this->GetLastValidDirection()));
		const FVector Dimensions(60, 60, 20);
		//DrawDebugBox(GetWorld(), PossibleNode->GetTileCoordinates(), Dimensions, FColor::Red);
		if (PossibleNode)
		{
			this->SetNextNodeByDir(TheGridGen->GetThreeDOfTwoDVector(PossibleNode->GetGridPosition() - this->GetLastNodeCoords()), true);
		}
	}

}

void ABlinky::resetGhost()
{
	const FVector2D BlinkySpawn = FVector2D(21, 13);
	CurrentGridCoords = BlinkySpawn;
	LastNode = *(GridGenTMap.Find(BlinkySpawn));
	NextNode = *(GridGenTMap.Find(BlinkySpawn));
	SetTargetNode(*(GridGenTMap.Find(BlinkySpawn)));
	SetActorLocation(FVector(2150.f,1350.f,5.f));
	bIsEaten = false;
}





