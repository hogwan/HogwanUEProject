// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile/ThrowObject.h"
#include "Stone.generated.h"

/**
 * 
 */
UCLASS()
class HOGWANPROJECT_API AStone : public AThrowObject
{
	GENERATED_BODY()
	
protected:
	void ColBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

private:
	UPROPERTY(EditAnywhere)
	float Damage = 10.f;

};
