// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerNode.h"

//default contstructor
APowerNode::APowerNode() {
	//enumerator for eatable objects(defined in parent)
	EEatable_id = Power;
	isEaten = false;

	Point_Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Point_Collider"));
	RootComponent = Point_Collider;

	Point_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Point_Mesh"));
	Point_Mesh->SetupAttachment(Point_Collider);

}

bool APowerNode::get_isEaten() {
	return isEaten;
}

void APowerNode::set_isEaten() {
	isEaten = true;
}


