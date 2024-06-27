// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "CharacterEnumType.h"
#include "Hunter.generated.h"

UCLASS()
class HOGWANPROJECT_API AHunter : public ACharacter
{
	GENERATED_BODY()

public:
	AHunter();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

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
	class UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* ShootAction;

	UPROPERTY(EditAnywhere, Category = "Montage")
	class UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	class UAnimMontage* ShootMontage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	class UAnimMontage* DodgeMontage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	class UAnimMontage* RollMontage;
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
	FORCEINLINE class UAttributeComponent* GetAttribute() { return Attribute; }
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
	void Interact(const FInputActionValue& Value);
	void Shoot(const FInputActionValue& Value);

	void TraceLockOnTarget(float DeltaTime);

	void ReleaseLockOn();
	void SetLockOn(class AMonster* Target);

	//  Components
	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* ViewCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UAttributeComponent* Attribute;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class AActor* LockOnTarget;

	bool bIsRun = false;
	bool bIsLockOn = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), category = "CharacterState")
	ECharacterActionState CurActionState = ECharacterActionState::ECAS_Unoccupied;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int AttackCount = 0;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool NextAttackChance = false;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool GoNextAttack = false;

	UPROPERTY(VisibleInstanceOnly)
	class AItem* OverlappingItem;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FVector InputVector = FVector::Zero();

public:
	void SetOverlappingItem(class AItem* Item) { OverlappingItem = Item; }
	class AItem* GetOverlappingItem() { return OverlappingItem; }
	
	UPROPERTY(BlueprintReadWrite)
	int CurWeaponSlot = 0;
	UPROPERTY(BlueprintReadWrite)
	int CurGunSlot = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AMeleeWeapon* EquipedMeleeWeapons;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ARangedWeapon* EquippedRangedWeapons;
};
