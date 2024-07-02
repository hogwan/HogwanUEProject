// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hunter/BBAnimInstance.h"
#include "BBHunterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class HOGWANPROJECT_API UBBHunterAnimInstance : public UBBAnimInstance
{
	GENERATED_BODY()

public:
	void NativeInitializeAnimation() override;
	void NativeUpdateAnimation(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly)
	class AHunter* Hunter;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	class UCharacterMovementComponent* HunterMovement;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	float MoveRotDegree;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	float GroundSpeed;
};
