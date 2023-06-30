// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GridBaseNode.h"
#include "GhostExitNode.generated.h"

/**
 * 
 */
UCLASS()
class PACMANGRID_API AGhostExitNode : public AGridBaseNode
{
	GENERATED_BODY()
public:
	AGhostExitNode();

	UPROPERTY(VisibleAnywhere)
		bool bIsExitOpen;
};
