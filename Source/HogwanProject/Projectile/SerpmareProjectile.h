// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SerpmareProjectile.generated.h"

UCLASS()
class HOGWANPROJECT_API ASerpmareProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ASerpmareProjectile();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class USphereComponent* Sphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit")
	class UNiagaraComponent* Flying;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit")
	class UNiagaraSystem* HitEffect;

	UPROPERTY(EditAnywhere)
	float LifeTime = 6.f;
protected:
	virtual void BeginPlay() override;
	
	virtual void ProjectileExplosion();

	UFUNCTION()
	void ProjectileCollide(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
