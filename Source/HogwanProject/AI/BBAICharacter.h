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
	void ChangeAnimation(uint8 _Type);

	template<typename EnumType>
	void ChangeAnimation(EnumType _Type)
	{
		ChangeAnimation(static_cast<uint8>(_Type));
	}

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
	bool TurnEnd = false;
	UPROPERTY(BlueprintReadWrite)
	bool AttackEnd = false;
	UPROPERTY(BlueprintReadWrite)
	bool HitEnd = false;
	UPROPERTY(BlueprintReadWrite)
	bool PerceiveEnd = false;

	UPROPERTY(EditInstanceOnly)
	TArray<FVector> PatrolPoints;

protected:
	void BeginPlay() override;


private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	uint8 AniValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBBAIAnimInstance* AnimInst;
};
