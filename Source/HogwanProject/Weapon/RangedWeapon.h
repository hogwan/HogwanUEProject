// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/Weapon.h"
#include "RangedWeapon.generated.h"

/**
 * 
 */
UCLASS()
class HOGWANPROJECT_API ARangedWeapon : public AWeapon
{
	GENERATED_BODY()
	
public:
	ARangedWeapon();
	void Tick(float DeltaTime) override;

protected:
	void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* BulletSpawnPoint;
};
