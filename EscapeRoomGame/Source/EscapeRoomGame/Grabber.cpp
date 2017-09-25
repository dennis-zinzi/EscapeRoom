// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	reach = 75.0f;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	UE_LOG(LogClass, Warning, TEXT("Grabber ready sir!"));
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	///Get the player viewpoint
	FVector pPos;
	FRotator pRot;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(pPos, pRot);

	//UE_LOG(LogClass, Warning, TEXT("Grabber:\n\tpos: %s \n\trot: %s"), *pPos.ToString(), *pRot.ToString());
	
	///Draw a red trace in the world to visualise
	FVector LineTraceEnd = pPos + (pRot.Vector() * reach);
	UKismetSystemLibrary::DrawDebugLine(GetWorld(), pPos, LineTraceEnd, FLinearColor::Blue, 0.0f, 10.0f);

	///Line-trace/Ray-cast out to reach distance
	FHitResult LineTraceHit;

	//Set up query params (using simple collision box, ignoring self)
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(LineTraceHit, pPos, LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParams);

	///See what we hit
	AActor *hitActor = LineTraceHit.GetActor();
	if(hitActor){
		UE_LOG(LogClass, Warning, TEXT("Hit: %s"), *hitActor->GetName());
	}
}

