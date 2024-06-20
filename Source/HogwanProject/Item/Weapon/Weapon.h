// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Item.h"
#include "Weapon.generated.h"

UENUM(BlueprintType)
enum class EEquipHand
{
	NONE,
	EEH_RightHand,
	EEH_LeftHand,
};

UCLASS()
class HOGWANPROJECT_API AWeapon : public AItem
{
	GENERATED_BODY()
	

public:
	AWeapon();

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	EEquipHand EquipHand = EEquipHand::NONE;

protected:
	void BeginPlay() override;
};
