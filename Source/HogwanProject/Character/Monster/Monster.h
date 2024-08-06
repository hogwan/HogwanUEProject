// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Character/Monster/BBAICharacter.h"
#include "Interface/HitInterface.h"
#include "Global/BBEnum.h"
#include "Monster.generated.h"

UCLASS()
class HOGWANPROJECT_API AMonster : public ABBAICharacter
{
	GENERATED_BODY()

public:
	AMonster();

	virtual void Tick(float DeltaTime) override;

	FORCEINLINE class UWidgetComponent* GetLockOnWidget() { return LockOnTargetWidget; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMonster MonsterEnum;

	TArray<AActor*> IgnoreArray;

	UFUNCTION(BlueprintCallable)
	void DisableHitBox();

	UFUNCTION(BlueprintCallable)
	void EnableHitBox();

	void GetHit(const FVector& ImpactPoint, AActor* Hitter, EHitType HitType) override;
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* MonsterHitBox;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* BoxTraceStart;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* BoxTraceEnd;

	UFUNCTION()
	void HitBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void Reset() override;

private:
	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* LockOnTargetWidget;


};
