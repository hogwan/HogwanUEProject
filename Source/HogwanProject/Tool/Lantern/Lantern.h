// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tool/InteractObject.h"
#include "Lantern.generated.h"

/**
 * 
 */
UCLASS()
class HOGWANPROJECT_API ALantern : public AInteractObject
{
	GENERATED_BODY()

public:
	ALantern();

	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	class UNiagaraComponent* TurnOnEffect;

	void Interact() override;
	void TurnOn();

	bool IsOn = false;

	UPROPERTY(EditAnywhere)
	float InteractDistance = 100.f;
	
};
