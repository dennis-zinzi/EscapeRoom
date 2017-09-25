// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	reach = 75.0f;
	PhysicsHandle = nullptr;
	InputComp = nullptr;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	///Search for attached physics handle
	PhysicsHandle = FindComponent<UPhysicsHandleComponent>();

	InputComp = FindComponent<UInputComponent>();
	if(InputComp){
		///Bind Input actions
		InputComp->BindAction("Grab", IE_Pressed, this, &UGrabber::GrabFunc);
		InputComp->BindAction("Grab", IE_Released, this, &UGrabber::ReleaseFunc);
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	///If the physics handle is attached
	if(PhysicsHandle->GrabbedComponent){
		///Move the object that we're holding
		PhysicsHandle->SetTargetLocation(GetLineTrace().end);
	}
}


FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	//Get LineTrace from player to reach position
	FLineTrace LineTrace = GetLineTrace();
	
	///Draw a red trace in the world to visualise
	//UKismetSystemLibrary::DrawDebugLine(GetWorld(), pPos, LineTraceEnd, FLinearColor::Blue, 0.0f, 10.0f);

	///Line-trace/Ray-cast out to reach distance
	FHitResult LineTraceHit;

	//Set up query params (using simple collision box, ignoring self)
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(LineTraceHit, LineTrace.start, LineTrace.end, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParams);
	
	return LineTraceHit;
}

void UGrabber::GrabFunc(){
	UE_LOG(LogClass, Warning, TEXT("Grabbing"));

	///Line Trace and see if we reach any actors with physics body collision channel set
	///See what we hit
	FHitResult HitRes = GetFirstPhysicsBodyInReach();

	AActor *HitActor = HitRes.GetActor();
	if(!HitActor){
		return;
		//UE_LOG(LogClass, Warning, TEXT("Hit: %s"), *hitActor->GetName());
	}

	//Get hit component
	UPrimitiveComponent *GrabComponent = HitRes.GetComponent();

	///If we hit something then attach a physics handle
	if(GrabComponent){
		///Attach physics handle (NAME_None as not a skeletal mesh/no bone name) and keep component with current rotation
		PhysicsHandle->GrabComponentAtLocationWithRotation(GrabComponent, NAME_None, GrabComponent->GetOwner()->GetActorLocation(), GrabComponent->GetOwner()->GetActorRotation());
	}
}

void UGrabber::ReleaseFunc(){
	UE_LOG(LogClass, Warning, TEXT("Releasing"));

	///Remove physics handle
	if(PhysicsHandle->GrabbedComponent){
		PhysicsHandle->ReleaseComponent();
	}
}

FLineTrace UGrabber::GetLineTrace() const{
	///Get the player viewpoint
	FVector pPos;
	FRotator pRot;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(pPos, pRot);

	//Calculate end of line trace
	FVector LineTraceEnd = pPos + (pRot.Vector() * reach);

	FLineTrace LineTrace = {pPos, LineTraceEnd};
	return LineTrace;
}
