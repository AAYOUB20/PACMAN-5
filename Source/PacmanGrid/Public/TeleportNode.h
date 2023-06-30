// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GridBaseNode.h"
#include "TeleportNode.generated.h"

/**
 * 
 */
UCLASS()
class PACMANGRID_API ATeleportNode : public AGridBaseNode
{
	GENERATED_BODY()
public:
	//teleport node properties
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Static_Mesh;

	UPROPERTY(EditAnywhere)
		UBoxComponent* Point_Collider;

	ATeleportNode();
	
};
