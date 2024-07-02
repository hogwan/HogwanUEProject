// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/BBAnimInstance.h"
#include "BBAIAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class HOGWANPROJECT_API UBBAIAnimInstance : public UBBAnimInstance
{
	GENERATED_BODY()
	

public:
	UPROPERTY(EditAnywhere, Category = "Montage")
	class UAnimMontage* TurnMontage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	class UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	class UAnimMontage* HitMontage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	class UAnimMontage* PerceiveMontage;
};
