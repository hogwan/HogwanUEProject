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
	class UAnimMontage* DashAttackMontage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	class UAnimMontage* FrontHitMontage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	class UAnimMontage* BackHitMontage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	class UAnimMontage* PerceiveMontage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	class UAnimMontage* IdleMontage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	class UAnimMontage* WalkMontage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	class UAnimMontage* RunMontage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	class UAnimMontage* FrontStunMontage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	class UAnimMontage* BackStunMontage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	class UAnimMontage* BackstepMontage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	class UAnimMontage* LullMontage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	class UAnimMontage* TakeDownBack;

	UPROPERTY(EditAnywhere, Category = "Montage")
	class UAnimMontage* NormalTakeDown;

	UPROPERTY(EditAnywhere, Category = "Montage")
	class UAnimMontage* GreatSwordTakeDown;

	UPROPERTY(EditAnywhere, Category = "Montage")
	class UAnimMontage* KatanaTakeDown;

	UPROPERTY(EditAnywhere, Category = "Montage")
	class UAnimMontage* BackWalkMontage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	class UAnimMontage* ShootMontage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	class UAnimMontage* DodgeMontage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	class UAnimMontage* PatternTermMontage;
};
