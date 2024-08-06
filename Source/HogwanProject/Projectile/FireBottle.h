// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile/ThrowObject.h"
#include "FireBottle.generated.h"

/**
 * 
 */
UCLASS()
class HOGWANPROJECT_API AFireBottle : public AThrowObject
{
	GENERATED_BODY()
	
protected:
	void ColBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AExplosion> Explosion;

};
