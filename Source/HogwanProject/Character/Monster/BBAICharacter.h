// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "Character/Monster/BBAIAnimInstance.h"
#include "BBAICharacter.generated.h"

/**
 * 
 */
UCLASS()
class HOGWANPROJECT_API ABBAICharacter : public ABaseCharacter
{
	GENERATED_BODY()
	

public:
	ABBAICharacter();

	FORCEINLINE UBBAIAnimInstance* GetBBAIAnimInstance()
	{
		return AnimInst;
	}

	UFUNCTION(BlueprintPure, BlueprintCallable)
	class ABBAIController* GetBBAIController();
	
	float IdleTime = 3.f;
	float IdleAcc = IdleTime;
	float PerceiveRange = 300.f;
	float AttackRange = 80.f;
	float DestroyTime = 20.f;

	int PatrolNum = 0;
	bool PerceiveHunter = false;

	UPROPERTY(BlueprintReadWrite)
	bool Parriable = false;
	UPROPERTY(BlueprintReadWrite)
	bool TurnEnd = false;
	UPROPERTY(BlueprintReadWrite)
	bool AttackEnd = false;
	UPROPERTY(BlueprintReadWrite)
	bool UnableEnd = false;
	UPROPERTY(BlueprintReadWrite)
	bool PerceiveEnd = false;

	UPROPERTY(EditInstanceOnly)
	TArray<FVector> PatrolPoints;


	void GetHit(const FVector& ImpactPoint, AActor* Hitter, EHitType HitType) override;

	UFUNCTION(BlueprintCallable)
	void DeathCheck();

protected:
	void BeginPlay() override;

	bool BackHit(AActor* Hitter);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* FrontTakeDownBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* BackTakeDownBox;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBBAIAnimInstance* AnimInst = nullptr;

	UFUNCTION()
	void FrontTakeDownBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void FrontTakeDownBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void BackTakeDownBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void BackTakeDownBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


};
