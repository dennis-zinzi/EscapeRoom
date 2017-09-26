// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "GameFramework/Actor.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

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

		//Blueprint Event to Open Door
		UPROPERTY(BlueprintAssignable)
		FDoorEvent OnOpenDoor;

		//Blueprint Event to Close Door
		UPROPERTY(BlueprintAssignable)
		FDoorEvent OnCloseDoor;

	private:		
		UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
		float OpenAngle;

		UPROPERTY(EditAnywhere)
		ATriggerVolume *PressurePlate;

		UPROPERTY(EditAnywhere)
		float MassToOpen;

		//Know if door is open or closed
		bool isOpen;

		//Returns total mass on the trigger volume (in kg)
		float GetTotalMassOnPlate() const;
};
