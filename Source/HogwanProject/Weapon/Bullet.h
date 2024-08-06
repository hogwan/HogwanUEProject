// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class HOGWANPROJECT_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	ABullet();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float Damage = 5.f;
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* Sphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UNiagaraComponent* Flying;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UNiagaraSystem* HitEffect;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float Speed = 1000.f;


	UPROPERTY()
	float LifeTime = 1.f;
};
