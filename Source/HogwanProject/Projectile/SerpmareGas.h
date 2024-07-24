// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile/SerpmareProjectile.h"
#include "SerpmareGas.generated.h"

/**
 * 
 */
UCLASS()
class HOGWANPROJECT_API ASerpmareGas : public ASerpmareProjectile
{
	GENERATED_BODY()
public:
	void Tick(float _DeltaTime) override;

protected:
	void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 1000.f;
};
