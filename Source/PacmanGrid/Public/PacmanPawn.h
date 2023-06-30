// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GridPawn.h"
#include "GridGenerator.h"
#include "GridPlayerController.h"
#include "PointNode.h"
#include "PowerNode.h"
#include "GridBaseNode.h"
#include "PacmanWidget.h"
#include "PacmanPawn.generated.h"


/**
 * 
 */
UCLASS()
class PACMANGRID_API APacmanPawn : public AGridPawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APacmanPawn();
	virtual void Tick(float DeltaTime) override;
	virtual void SetVerticalInput(float AxisValue) override;
	virtual void SetHorizontalInput(float AxisValue) override;
	// called on left mouse click (binding)
	virtual	void OnClick() override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//called when lives counter reaches zero
	void resetLevel();
	bool isGameOver;

	//User Interface
	UPROPERTY(EditAnywhere, Category = "User Interface")
		TSubclassOf<class UUserWidget> UIClass;

	UPROPERTY(EditAnywhere, Category = "User Interface")
		UPacmanWidget* UIWidget;
	
	UFUNCTION(BlueprintCallable)
		bool IsSuperPowerEnabled()
	{
		return bIsSuperCiboConsumet;
	}

	UFUNCTION(BlueprintCallable)
		int32 GetDotsCount()
	{
		return DotsCount;
	}


protected:

	UPROPERTY(EditAnywhere, Category = "Movement")
		float PacmanNormalSpeed;
	UPROPERTY(EditAnywhere, Category = "Movement")
		float PacmanPowerSpeed;
	UPROPERTY(VisibleAnywhere)
		int32 DotsCount;
	UPROPERTY(VisibleAnywhere)
		int32 PowerDotsCount;


	FTimerHandle DeathTimerHandle;

	float DeathTimer;
	virtual void BeginPlay() override;
	virtual void HandleMovement() override;
	virtual void SetTargetNode(AGridBaseNode* Node) override;
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	FString GameOverText;

private:
	FTimerHandle FrightenedModeTimer;
	void SuperPowerLost();

	bool bIsSuperCiboConsumet = false;

};
