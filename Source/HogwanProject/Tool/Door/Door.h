// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tool/InteractObject.h"
#include "Door.generated.h"

/**
 * 
 */
UCLASS()
class HOGWANPROJECT_API ADoor : public AInteractObject
{
	GENERATED_BODY()
	
public:
	ADoor();

	void Tick(float DeltaTime) override;

	void Interact() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* Door;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* DoorRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* DoorLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* HunterPos;

private:
	bool IsOpen = false;

	UPROPERTY(EditAnywhere)
	float RotSpeed = 8.5f;

	UPROPERTY(EditAnywhere)
	float RotTime = 7.f;

	void DoorRotate(float _DeltaTime);

};
