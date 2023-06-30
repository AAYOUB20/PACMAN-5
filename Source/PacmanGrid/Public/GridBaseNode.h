// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "GridBaseNode.generated.h"

UENUM()
enum EWalkableId { NotWalkable, Walkable };

UENUM()
enum ENode_type {Point, Power, NotEatable};

UCLASS()
class PACMANGRID_API AGridBaseNode : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridBaseNode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//added to differentiate eatable from not eatable actors
	UPROPERTY(EditAnywhere)
		//by default set to not eatable
		TEnumAsByte<ENode_type> EEatable_id;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		TEnumAsByte<EWalkableId> EWalkableId = Walkable;

	TEnumAsByte<ENode_type> get_EEatable_id();

	// set the (x, y) position
	void SetGridPosition(const double InX, const double InY);

	// get the (x, y) position
	FVector2D GetGridPosition() const;

	// (x, y) position of the tile
	UPROPERTY(EditAnywhere)
		FVector2D TileGridPosition;

	// FVector position of the tile
	UPROPERTY(EditAnywhere)
		FVector TileCoordinatesPosition;

	FVector GetTileCoordinates();

	UPROPERTY(EditAnywhere)
		bool IsEatable;
	UFUNCTION(BlueprintCallable)
		bool CanBeEat();

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditAnywhere)
		UBoxComponent* Collider;

};
