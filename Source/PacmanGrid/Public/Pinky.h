// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhantomPawn.h"
#include "Pinky.generated.h"

/**
 * 
 */
UCLASS()
class PACMANGRID_API APinky : public APhantomPawn
{
	GENERATED_BODY()
		virtual AGridBaseNode* GetPlayerRelativeTarget() override;

public:
	APinky();

	void BeginPlay();


	void SetScatterTarget() override;

	void SetChaseTarget() override;

	void SetEatenTarget() override;

	void resetGhost() override;

	void ghostWait() override;

private:
	UPROPERTY(VisibleAnywhere)
		AGridBaseNode* ScatterTarget;

};

