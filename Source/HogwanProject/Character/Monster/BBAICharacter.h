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

	void Tick(float DeltaTime) override;

	FORCEINLINE UBBAIAnimInstance* GetBBAIAnimInstance()
	{
		return AnimInst;
	}

	UFUNCTION(BlueprintPure, BlueprintCallable)
	class ABBAIController* GetBBAIController();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EHitType HitType = EHitType::EHT_Light;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterStatus")
	float IdleTime = 3.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterStatus")
	float IdleAcc = IdleTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterStatus")
	float WaitTime = 3.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterStatus")
	float WaitAcc = WaitTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterStatus")
	float WalkSpeed = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterStatus")
	float RunSpeed = 400.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterStatus")
	float PerceiveRange = 300.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterStatus")
	float AttackRange = 80.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterStatus")
	float DestroyTime = 20.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterStatus")
	float AttackCoolTime = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterStatus")
	float CurLullTime = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterStatus")
	float MaxLullTime = 2.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterStatus")
	float StaminaRecoverSpeed = 20.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterStatus")
	float BackstepDistance = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterStatus")
	float DashAttackDistance = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterStatus")
	float BackWalkDistance = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterStatus")
	float PunchDistance = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterStatus")
	float RotateSpeed = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterStatus")
	float BasicDamage = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterStatus")
	float Damage = BasicDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterStatus")
	EDir MonsterDir = EDir::None;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterStatus")
	EToughness Toughness = EToughness::None;

	UPROPERTY(EditInstanceOnly)
	TArray<AActor*> PatrolPoints;

	UPROPERTY(BlueprintReadWrite)
	int PatrolNum = 0;
	UPROPERTY(BlueprintReadWrite)
	bool PerceiveHunter = false;
	UPROPERTY(BlueprintReadWrite)
	bool CanGrabType = true;

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
	UPROPERTY(BlueprintReadWrite)
	bool BackstepEnd = false;
	UPROPERTY(BlueprintReadWrite)
	bool LullEnd = false;
	UPROPERTY(BlueprintReadWrite)
	bool IsGrapped = false;

	void GetHit(const FVector& ImpactPoint, AActor* Hitter, EHitType HitType) override;

	UFUNCTION(BlueprintCallable)
	void DeathCheck();

protected:
	void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* FrontTakeDownBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* BackTakeDownBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UPawnSensingComponent* PawnSensing;

	UFUNCTION()
	void OnSeePawn(APawn* Pawn);

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

	UPROPERTY()
	bool IsDeath = false;
};
