// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//Initialize member variables
	OpenAngle = -75.0f;
	PressurePlate = nullptr;
	isOpen = false;
	MassToOpen = 50.0f;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	//Check Pressure Plate not null
	if(!PressurePlate){
		UE_LOG(LogClass, Error, TEXT("NO PRESSURE PLATE"));
		return;
	}
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Check Pressure Plate not null
	if(!PressurePlate){ 
		return; 
	}

	//Open Door if enough mass on pressure plate and door is closed
	if(!isOpen && GetTotalMassOnPlate() >= MassToOpen){
		//Trigger Blueprint event
		OnOpenDoor.Broadcast();
		isOpen = true;
	}

	//Close door if not enough mass on pressure plate and door is open
	if(isOpen && GetTotalMassOnPlate() < MassToOpen){
		//Trigger Blueprint event
		OnCloseDoor.Broadcast();
		isOpen = false;
	}

}


float UOpenDoor::GetTotalMassOnPlate() const
{
	float TotMass = 0.0f;

	//Find all overlapping Actors
	TArray<AActor*> ActorsOnPlate;
	PressurePlate->GetOverlappingActors(ActorsOnPlate);

	//Iterate through the actors and add their masses
	for(const auto a : ActorsOnPlate){
		TotMass += a->FindComponentByClass<UPrimitiveComponent>()->CalculateMass();
	}
	//UE_LOG(LogClass, Warning, TEXT("Tot Mass: %f"), TotMass);
	return TotMass;
}
