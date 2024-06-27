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

	UFUNCTION(BlueprintCallable)
	FORCEINLINE FVector GetDir() { return Dir; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetDir(FVector _Dir) { Dir = _Dir; }

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* Sphere;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FVector Dir = FVector::Zero();

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float Speed = 1000.f;

	UPROPERTY()
	float LifeTime = 1.f;
};
