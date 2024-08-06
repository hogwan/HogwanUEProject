// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Explosion.generated.h"

UCLASS()
class HOGWANPROJECT_API AExplosion : public AActor
{
	GENERATED_BODY()
	
public:	
	AExplosion();

	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	class USphereComponent* Sphere;

	UPROPERTY(EditAnywhere)
	class UNiagaraComponent* Effect;

	UPROPERTY(EditAnywhere)
	float LifeTime = 0.1f;

	UPROPERTY(EditAnywhere)
	float Damage = 100.f;

	UFUNCTION()
	void ColBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
