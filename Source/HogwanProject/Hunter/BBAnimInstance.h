// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BBAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class HOGWANPROJECT_API UBBAnimInstance : public UAnimInstance
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
