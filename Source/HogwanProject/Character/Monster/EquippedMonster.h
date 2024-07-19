// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Monster/Monster.h"
#include "EquippedMonster.generated.h"

/**
 * 
 */
UCLASS()
class HOGWANPROJECT_API AEquippedMonster : public AMonster
{
	GENERATED_BODY()
public:
	AEquippedMonster();

	void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void DisableRightHandHitBox();

	UFUNCTION(BlueprintCallable)
	void DisableLeftHandHitBox();

	UFUNCTION(BlueprintCallable)
	void EnableRightHandHitBox();

	UFUNCTION(BlueprintCallable)
	void EnableLeftHandHitBox();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AWeapon* RightHandWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AWeapon* LeftHandWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AMeleeWeapon> MutantRightHandWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AMeleeWeapon> MutantLeftHandWeapon;


	void Reset() override;

	void GetHit(const FVector& ImpactPoint, AActor* Hitter, EHitType HitType) override;

	void EquipRightHandWeapon();
	void EquipLeftHandWeapon();

};
