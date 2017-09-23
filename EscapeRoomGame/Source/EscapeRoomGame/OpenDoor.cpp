// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	OpenAngle = 90.0f;
	PressurePlate = nullptr;
	ActivationActor = nullptr;
	isOpen = false;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Poll the Trigger Volume
	auto p1 = (AActor*)UGameplayStatics::GetPlayerController(this, 0)->GetPawn();
	//Open Door if ActivationActor is in the volume
	if(!isOpen && (PressurePlate->IsOverlappingActor(p1) || PressurePlate->IsOverlappingActor(ActivationActor))){
		//Find the owning object
		auto owner = GetOwner();
		auto rot = FRotator(0.0f, -75.0f, 0.0f);

		owner->AddActorLocalRotation(rot);
		//UE_LOG(LogClass, Warning, TEXT("Current Rot: %s"), *rot.ToString());
		isOpen = true;
	}
}

