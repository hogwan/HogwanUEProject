// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Monster/BBAICharacter.h"
#include "Serpmare.generated.h"

/**
 * 
 */
UCLASS()
class HOGWANPROJECT_API ASerpmare : public ABBAICharacter
{
	GENERATED_BODY()
	
public:
	ASerpmare();

	virtual void Tick(float DeltaTime) override;

	FORCEINLINE class UWidgetComponent* GetLockOnWidget() { return LockOnTargetWidget; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMonster MonsterEnum;

	void GetHit(const FVector& ImpactPoint, AActor* Hitter, EHitType HitType) override;

	UFUNCTION(BlueprintCallable)
	void DisableHitBox();

	UFUNCTION(BlueprintCallable)
	void EnableHitBox();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void HitBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void Reset() override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxCol;
};
