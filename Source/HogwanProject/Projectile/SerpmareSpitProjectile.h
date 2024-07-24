// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile/SerpmareProjectile.h"
#include "SerpmareSpitProjectile.generated.h"

/**
 * 
 */
UCLASS()
class HOGWANPROJECT_API ASerpmareSpitProjectile : public ASerpmareProjectile
{
	GENERATED_BODY()
	

public:
	ASerpmareSpitProjectile();

	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* ProjectileMovementComponent;
};
