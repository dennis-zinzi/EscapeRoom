// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "GameFramework/Actor.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEROOMGAME_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

	public:	
		// Sets default values for this component's properties
		UOpenDoor();

	protected:
		// Called when the game starts
		virtual void BeginPlay() override;

	public:	
		// Called every frame
		virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	private:
		UPROPERTY(EditAnywhere)
		float OpenAngle;
		
		UPROPERTY(EditAnywhere)
		ATriggerVolume *PressurePlate;
	
		//UPROPERTY(EditAnywhere)
		//AActor *ActivationActor;

		UPROPERTY(EditAnywhere)
		float MassToOpen;
		
		UPROPERTY(EditAnywhere)
		float DoorCloseDelay;

		float LastOpenTime;
		bool isOpen;

		//Rotates Door
		void RotateDoor(float angle);
		//Returns total mass on the trigger volume (in kg)
		float GetTotalMassOnPlate() const;
};
