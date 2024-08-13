// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tool/InteractObject.h"
#include "DoorSwitch.generated.h"

/**
 * 
 */
UCLASS()
class HOGWANPROJECT_API ADoorSwitch : public AInteractObject
{
	GENERATED_BODY()
	
public:

	ADoorSwitch();

	void Interact() override;

	UPROPERTY(EditAnywhere)
	class AIronDoor* ConnectedDoor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* HunterPos;

	void OpenDoor();
};
