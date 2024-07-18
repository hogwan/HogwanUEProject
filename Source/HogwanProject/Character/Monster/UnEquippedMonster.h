// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Monster/Monster.h"
#include "UnEquippedMonster.generated.h"

/**
 * 
 */
UCLASS()
class HOGWANPROJECT_API AUnEquippedMonster : public AMonster
{
	GENERATED_BODY()

public:
	AUnEquippedMonster();

	void BeginPlay() override;

	TArray<AActor*> IgnoreArray;

	UFUNCTION(BlueprintCallable)
	void DisableHitBox();

	UFUNCTION(BlueprintCallable)
	void EnableHitBox();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* MonsterHitBox;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* BoxTraceStart;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* BoxTraceEnd;

	UFUNCTION()
	void HitBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void Reset() override;

	void GetHit(const FVector& ImpactPoint, AActor* Hitter, EHitType HitType) override;

};
