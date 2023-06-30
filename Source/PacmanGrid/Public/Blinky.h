// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhantomPawn.h"
#include "Blinky.generated.h"


/**
 * 
 */
UCLASS()
class PACMANGRID_API ABlinky : public APhantomPawn
{
	GENERATED_BODY()
	virtual AGridBaseNode* GetPlayerRelativeTarget() override;

public:
	ABlinky();

	void BeginPlay();


	void SetScatterTarget() override;

	void SetChaseTarget() override;

	void SetEatenTarget() override;

	void resetGhost() override;

private:
	UPROPERTY(VisibleAnywhere)
		AGridBaseNode* ScatterTarget;

};
