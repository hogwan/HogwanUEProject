// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "AI/BBAIAnimInstance.h"
#include "BBAICharacter.generated.h"

/**
 * 
 */
UCLASS()
class HOGWANPROJECT_API ABBAICharacter : public ABaseCharacter
{
	GENERATED_BODY()
	

public:
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
	
	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected:
	void BeginPlay() override;

	bool BackHit(AActor* Hitter);
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBBAIAnimInstance* AnimInst;
};
