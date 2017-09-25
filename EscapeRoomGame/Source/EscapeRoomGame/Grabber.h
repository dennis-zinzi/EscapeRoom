// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include <string>
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEROOMGAME_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	private:
		//How far ahead of the player can we reach to grab (cm)
		UPROPERTY(EditAnywhere)
		float reach;

		UPhysicsHandleComponent *PhysicsHandle;
		UInputComponent *InputComp;
	
		//Get hit for first physics body in reach
		FHitResult GetFirstPhysicsBodyInReach() const;

		//Ray-cast and grab what's in reach
		void GrabFunc();

		//Realease grab/hold of object
		void ReleaseFunc();

		//Finds (assumed) attached component
		template<typename T>
		T* FindComponent();
};


template<typename T>
inline T* UGrabber::FindComponent(){
	auto comp = GetOwner()->FindComponentByClass<T>();
	if(!comp){
		UE_LOG(LogClass, Error, TEXT("No %s found on %s"), *FString(std::string(typeid(T).name()).c_str()), *(GetOwner()->GetName()));
		return nullptr;
	}

	return comp;
}
