// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
//#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	OpenAngle = 75.0f;
	PressurePlate = nullptr;
	ActivationActor = nullptr;
	isOpen = false;
	DoorCloseDelay = 10.0f;
	LastOpenTime = 0.0f;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	//Get Player Actor
	ActivationActor = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Poll the Trigger Volume
	//Open Door if ActivationActor is in the volume
	if(!isOpen && PressurePlate->IsOverlappingActor(ActivationActor)){
		RotateDoor(-OpenAngle);
		LastOpenTime = GetWorld()->GetTimeSeconds();
	}

	
	if(isOpen){
		if(GetWorld()->GetTimeSeconds() - LastOpenTime > DoorCloseDelay){
			RotateDoor(OpenAngle);
		}
	}

}

void UOpenDoor::RotateDoor(float angle){
	//Find the owning object and rotate it
	GetOwner()->AddActorLocalRotation(FRotator(0.0f, angle, 0.0f));

	isOpen = angle >= 0.0f ? false : true;
}
