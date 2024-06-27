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
	
	UFUNCTION(BlueprintCallable)
	void SpawnBullet();
protected:
	void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* BulletSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ABullet> BP_Bullet = nullptr;

};
