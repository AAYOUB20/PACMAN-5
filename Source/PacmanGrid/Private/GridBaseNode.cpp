// Fill out your copyright notice in the Description page of Project Settings.


#include "GridBaseNode.h"

// Sets default values
AGridBaseNode::AGridBaseNode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = Collider;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMesh->SetupAttachment(Collider);

}

// Called when the game starts or when spawned
void AGridBaseNode::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGridBaseNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TEnumAsByte<ENode_type> AGridBaseNode::get_EEatable_id() {
	return EEatable_id;
}

void AGridBaseNode::SetGridPosition(const double InX, const double InY)
{
	TileGridPosition.Set(InX, InY);
}

FVector2D AGridBaseNode::GetGridPosition() const
{
	return TileGridPosition;
}

FVector AGridBaseNode::GetTileCoordinates()
{
	return TileCoordinatesPosition;
}

bool AGridBaseNode::CanBeEat()
{
	return IsEatable;
}


