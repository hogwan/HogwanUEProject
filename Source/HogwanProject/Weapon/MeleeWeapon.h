// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/Weapon.h"
#include "MeleeWeapon.generated.h"

/**
 * 
 */
UCLASS()
class HOGWANPROJECT_API AMeleeWeapon : public AWeapon
{
	GENERATED_BODY()

public:
	AMeleeWeapon();
	void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void HitBoxOn();

	UFUNCTION(BlueprintCallable)
	void HitBoxOff();

protected:
	void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* HitBox;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* BoxTraceStart;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* BoxTraceEnd;
	
	TArray<AActor*> IgnoreArray;

	UFUNCTION()
	void HitBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
