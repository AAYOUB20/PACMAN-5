// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GridBaseNode.h"
#include "Components/BoxComponent.h"
#include "PowerNode.generated.h"

/**
 * 
 */
UCLASS()
class PACMANGRID_API APowerNode : public AGridBaseNode
{
	GENERATED_BODY()

protected:
	//mi serve per capire se il punto è già stato mangiato (condizione nel pacman node)
	UPROPERTY(VisibleAnywhere)
		bool isEaten;
public:
	//aggiungiamo le proprietà del point node
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Point_Mesh;

	UPROPERTY(EditAnywhere)
		UBoxComponent* Point_Collider;

	//Costruttore
	APowerNode();

	//getter
	bool get_isEaten();

	//setter
	void set_isEaten();
};



