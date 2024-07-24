// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile/SerpmareProjectile.h"
#include "SerpmareFollowProjectile.generated.h"

/**
 * 
 */
UCLASS()
class HOGWANPROJECT_API ASerpmareFollowProjectile : public ASerpmareProjectile
{
	GENERATED_BODY()
public:
	void Tick(float _DeltaTime) override;

protected:
	void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float IdleTime = 3.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float IdleAcc = IdleTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool FollowTarget = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* Target = nullptr;
};
