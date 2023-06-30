// Fill out your copyright notice in the Description page of Project Settings.


#include "PhantomPawn.h"
#include "PacmanPawn.h"
#include "Kismet/GameplayStatics.h"
#include "TestGridGameMode.h"

APhantomPawn::APhantomPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ChaseGhostSpeed = 844.0f;
	HouseGhostSpeed = 800.0f;
	FrightenedGhostSpeed = 563.0f;
	EatenGhostSpeed = 2000.0f;

	StaticMeshBlue = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Blue Mesh"));
	StaticMeshWhite = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("White Mesh"));

	StaticMeshLeftEye = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left Eye Mesh"));
	StaticMeshRightEye = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right Eye Mesh"));

	StaticMeshBlue->SetupAttachment(Collider);
	StaticMeshWhite->SetupAttachment(Collider);
	StaticMeshLeftEye->SetupAttachment(Collider);
	StaticMeshRightEye->SetupAttachment(Collider);

	StaticMeshBlue->SetVisibility(false);
	StaticMeshWhite->SetVisibility(false);
	StaticMeshLeftEye->SetVisibility(false);
	StaticMeshRightEye->SetVisibility(false);

	Flash_time = 0.35f;
	RandomSeed = 15;
	RandMIN = 0;
	RandMAX = 1000000;

	//initializing vector used to determine random direction
	//up
	Direction_vector[0] = FVector(1, 0, 0);
	//down
	Direction_vector[1] = FVector(-1, 0, 0);
	//right
	Direction_vector[2] = FVector(0, 1, 0);
	//left
	Direction_vector[3] = FVector(0, -1, 0);





}

void APhantomPawn::EatenMode()
{
	StaticMeshBlue->SetVisibility(false);
	StaticMeshWhite->SetVisibility(false);
	StaticMesh->SetVisibility(false);
	StaticMeshLeftEye->SetVisibility(true);
	StaticMeshRightEye->SetVisibility(true);
}

void APhantomPawn::resetEatenGhostCounter()
{
	EatenGhostCounter = 0;
}

int8 APhantomPawn::getEatenGhostCounter()
{
	return EatenGhostCounter;
}
//method to reset position and behaviour of ghosts once pacman gets eaten or game is finished
void APhantomPawn::resetGhost()
{
	//overridden in child
}

void APhantomPawn::ghostWait()
{
	//overridden in children
}

void APhantomPawn::setGhostExitPoints(int8 points)
{
	ghostExitPoints = points;
}


void APhantomPawn::leaveHouse()
{
	SetTargetNode(*GridGenTMap.Find(FVector2D(21,13)));
	bIsWaiting= false;
}

void APhantomPawn::BeginPlay()
{
	Super::BeginPlay();
	FVector2D StartNode = TheGridGen->GetXYPositionByRelativeLocation(GetActorLocation());
	LastNode = TheGridGen->TileMap[StartNode];
	Player = Cast<APacmanPawn>(UGameplayStatics::GetActorOfClass(GetWorld(), APacmanPawn::StaticClass()));


}

void APhantomPawn::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	const auto PN = Cast<APacmanPawn>(OtherActor);
	if (PN)
	{
		//PN->Eat();
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Ti lo trovato ...")));
	}
}

void APhantomPawn::OnNodeReached()
{
	Super::OnNodeReached();
}


void APhantomPawn::flipDirection()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("direction flipped")));
	LastValidInputDirection = ( - 1)*LastValidInputDirection;
}

void APhantomPawn::VisibleWhite()
{
	if (!bIsEaten && GameMode->flash_count<6) {
		GameMode->flash_count++;
		StaticMeshBlue->SetVisibility(false);
		StaticMeshWhite->SetVisibility(true);
		GetWorld()->GetTimerManager().SetTimer(FlashTimer, this, &APhantomPawn::VisibleBlue, Flash_time, false);
	}

}

void APhantomPawn::VisibleBlue()
{
	if (GameMode->bIsFlashing) {
		if (!bIsEaten) {
			StaticMeshBlue->SetVisibility(true);
			GetWorld()->GetTimerManager().SetTimer(FlashTimer, this, &APhantomPawn::VisibleWhite, Flash_time, false);
		}
	}
	else
		StaticMeshBlue->SetVisibility(true);
}

void APhantomPawn::ResetOriginalColor()
{
	StaticMeshLeftEye->SetVisibility(false);
	StaticMeshRightEye->SetVisibility(false);
	StaticMeshBlue->SetVisibility(false);
	StaticMeshWhite->SetVisibility(false);
	StaticMesh->SetVisibility(true);
}



void APhantomPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (this->GetTargetNode() == nullptr)
	{
		//if the ghost are in the waiting state, they will follow the ghostWait() behaviour
		if (!bIsWaiting) {
			if (!bIsEaten) {

				if (GameMode->CurrentState == EState::Chase) {
					ResetOriginalColor();
					SetChaseTarget();
					SetSpeed(ChaseGhostSpeed);
				}
				else if (GameMode->CurrentState == EState::Scatter) {
					ResetOriginalColor();
					SetScatterTarget();
					SetSpeed(ChaseGhostSpeed);
				}
				else if (GameMode->CurrentState == EState::Frightened) {
					SetFrightenedTarget();
					SetSpeed(FrightenedGhostSpeed);
				}
			}
			else
			{
				SetEatenTarget();
				SetSpeed(EatenGhostSpeed);
			}

		}
		else
			ghostWait();
		
	}
}

APacmanPawn* APhantomPawn::GetPlayer() const
{
	return Player;
}

void APhantomPawn::SetSpeed(float Speed)
{
	CurrentMovementSpeed = Speed;
}

AGridBaseNode* APhantomPawn::GetPlayerRelativeTarget()
{
	return Player->GetLastNode();
}

void APhantomPawn::SetFrightenedTarget() 
{
	if (!bIsEaten) {
		uint32 index;
		AGridBaseNode* TargetPtr;
		FVector2D TargetCoordinates;
		int32 randNum = RandomGenerator.RandRange(RandMIN, RandMAX);
		if (randNum >= 0 && randNum < 250000)
			index = 0;
		else if (randNum >= 250000 && randNum < 500000)
			index = 1;
		else if (randNum >= 500000 && randNum < 750000)
			index = 2;
		else
			index = 3;
		// random number
		for (int i = 0; i < 4; i++) {
			if (bIsEaten)
				break;
			TargetCoordinates = CurrentGridCoords + TheGridGen->GetTwoDOfVector(Direction_vector[index]);
			//quando il ghost entra nel teleport
			if (TargetCoordinates == FVector2D(18, 28))
				TargetCoordinates = FVector2D(18, 27);
			else if (TargetCoordinates == FVector2D(18, -1))
				TargetCoordinates = FVector2D(18, 0);

			TargetPtr = *(GridGenTMap.Find(TargetCoordinates));

			if ((Direction_vector[index] != -LastValidInputDirection) && (TheGridGen->IsNodeValidForWalk(TargetPtr))) {
				AGridBaseNode* PossibleNode = TheGridGen->GetClosestNodeFromMyCoordsToTargetCoords(this->GetLastNodeCoords(), TargetPtr->GetGridPosition(), -(this->GetLastValidDirection()));


				if (PossibleNode)
				{
					this->SetNextNodeByDir(TheGridGen->GetThreeDOfTwoDVector(PossibleNode->GetGridPosition() - this->GetLastNodeCoords()), true);
				}
				break;
			}

			else
				index = (index + 1) % 4;

		}
	}


}

void APhantomPawn::SetEatenTarget()
{
	
}





bool APhantomPawn::getIsWaiting()
{
	return bIsWaiting;
}

void APhantomPawn::SetChaseTarget()
{
	
}

void APhantomPawn::SetScatterTarget()
{
	
}


