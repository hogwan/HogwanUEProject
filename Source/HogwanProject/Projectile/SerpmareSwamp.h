// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SerpmareSwamp.generated.h"

UCLASS()
class HOGWANPROJECT_API ASerpmareSwamp : public AActor
{
	GENERATED_BODY()
	
public:	
	ASerpmareSwamp();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* HitBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UNiagaraComponent* SwampEffect;

	UFUNCTION(BlueprintCallable)
	void HitBoxOn();

	UFUNCTION(BlueprintCallable)
	void HitBoxOff();

	float DamageTickTime = 1.f;
	float DamageTickTimeAcc = 1.f;
	bool IsHitBoxOn = false;

	float LifeTime = 5.f;

	UFUNCTION()
	void SwampCollide(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
