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

protected:
	void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	EEquipHand EquipHand = EEquipHand::NONE;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* HitBox;

	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
