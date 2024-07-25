// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "InputActionValue.h"
#include "CharacterEnumType.h"
#include "Animation/AnimMontage.h"
#include "Hunter.generated.h"


UCLASS()
class HOGWANPROJECT_API AHunter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AHunter();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void GetHit(const FVector& ImpactPoint, AActor* Hitter, EHitType HitType) override;

	void Reset() override;

	//Input
#pragma region Input
	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* RunAction;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* DodgeAction;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* LockOnAction;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* ChargeAttackAction;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* ShootAction;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* MeleeWeaponSwapAction;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* RangedWeaponSwapAction;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* DeformWeaponAction;
#pragma endregion

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float MoveRotDegree;

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool GetIsLockOn() { return bIsLockOn; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetIsLockOn(bool LockOn) { bIsLockOn = LockOn; }

	FORCEINLINE int GetAttackCount() { return AttackCount; }
	FORCEINLINE void SetAttackCount(int num) { AttackCount = num; }
	FORCEINLINE bool GetGoNextAttack() { return GoNextAttack; }
	FORCEINLINE void SetGoNextAttack(bool NextAttack) { GoNextAttack = NextAttack; }
	FORCEINLINE bool GetCanTakeDown() { return bCanTakeDown; }
	FORCEINLINE void SetCanTakeDown(bool _TakeDown) { bCanTakeDown = _TakeDown; }

	FORCEINLINE ECharacterActionState GetCurActionState() { return CurActionState; }
	
protected:
	virtual void BeginPlay() override;

private:
	void Move(const FInputActionValue& Value);
	void MoveEnd(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Run(const FInputActionValue& Value);
	void Dodge(const FInputActionValue& Value);
	void LockOn(const FInputActionValue& Value);
	void Attack(const FInputActionValue& Value);
	void ChargeAttack(const FInputActionValue& Value);
	void Interact(const FInputActionValue& Value);
	void Shoot(const FInputActionValue& Value);
	void MeleeWeaponSwap(const FInputActionValue& Value);
	void RangedWeaponSwap(const FInputActionValue& Value);
	void DeformWeapon(const FInputActionValue& Value);

	void TraceLockOnTarget(float DeltaTime);

	void ReleaseLockOn();
	void SetLockOn(class AMonster* Target);

	UFUNCTION(BlueprintCallable)
	void Deform();

	FString GetDeformMontageName();

	//  Components
	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* ViewCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class AActor* LockOnTarget;

	bool bIsRun = false;
	bool bIsLockOn = false;
	bool bCanTakeDown = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), category = "CharacterState")
	ECharacterActionState CurActionState = ECharacterActionState::ECAS_Unoccupied;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), category = "CharacterState")
	ECharacterWeaponState CurWeaponState = ECharacterWeaponState::ECWS_Unoccupied;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int AttackCount = 0;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool NextAttackChance = false;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool GoNextAttack = false;

	UPROPERTY(VisibleInstanceOnly)
	class AItem* OverlappingItem;



	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TakeDown", meta = (AllowPrivateAccess = "true"))
	class AActor* TakeDownTarget;

	UPROPERTY(VisibleInstanceOnly, Category = "TakeDown")
	FVector TakeDownPos;

	UPROPERTY(VisibleInstanceOnly, Category = "TakeDown")
	FRotator TakeDownRot;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FVector InputVector = FVector::Zero();

public:
	void SetOverlappingItem(class AItem* Item) { OverlappingItem = Item; }
	void SetTakeDownInfo(class AActor* Target, const FVector& Pos, const FRotator& Rot);

	class AItem* GetOverlappingItem() { return OverlappingItem; }

	UFUNCTION(BlueprintCallable)
	void EquipWeapon(EWeapon Weapon);

	UFUNCTION(BlueprintCallable)
	void SwapWeapon(EWeaponType WeaponType, int32 ListNum);

	UFUNCTION(BlueprintCallable)
	FString GetWeaponStateToString(ECharacterWeaponState _WeaponState);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AMeleeWeapon* EquippedMeleeWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ARangedWeapon* EquippedRangedWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AWeapon* EquippedWeaponSheath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, UAnimMontage*> MontageMap;

	UPROPERTY(EditAnywhere)
	TArray<EWeapon> MeleeWeaponsInPocket;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<EWeapon> RangedWeaponsInPocket;

	UPROPERTY(EditAnywhere)
	TMap<EWeapon, TSubclassOf<class AWeapon>> WeaponList;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 CurMeleeListNum = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 CurRangedListNum = 0;

	UPROPERTY()
	int32 MaxListNum = 3;
};
