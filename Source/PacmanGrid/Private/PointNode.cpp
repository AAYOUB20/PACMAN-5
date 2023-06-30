// Fill out your copyright notice in the Description page of Project Settings.


#include "PointNode.h"

//default contstructor
APointNode::APointNode(){
	//enumerator for eatable objects(defined in parent)
	EEatable_id = Point;
	isEaten = false;

	Point_Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Point_Collider"));
	RootComponent = Point_Collider;

	Point_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Point_Mesh"));
	Point_Mesh->SetupAttachment(Point_Collider);

}

bool APointNode::get_isEaten() {
	return isEaten;
}

void APointNode::set_isEaten() {
	isEaten = true;
}

