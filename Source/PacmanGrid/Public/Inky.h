// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhantomPawn.h"
#include "Inky.generated.h"

/**
 * 
 */
UCLASS()
class PACMANGRID_API AInky : public APhantomPawn
{
	GENERATED_BODY()
		virtual AGridBaseNode* GetPlayerRelativeTarget() override;

public:
	AInky();

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
