// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "InputActionValue.h"
#include "CharacterEnumType.h"
#include "Animation/AnimMontage.h"
#include "Hunter.generated.h"

USTRUCT(BlueprintType)
struct FHunterStatus
{
	GENERATED_BODY()

	int Level = 1;
	int Gold = 0;
	int DisplayGold = 0;

	int Vitality = 0;
	int Endurance = 0;

	UPROPERTY(BlueprintReadWrite)
	int Strength = 0;
};

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
	class UInputAction* ThrowAction;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* DrinkAction;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* MeleeWeaponSwapAction;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* RangedWeaponSwapAction;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* UseItemSwapAction;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* DeformWeaponAction;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* OpenStatusInventoryAction;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* OpenQuickSlotAction;
#pragma endregion

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float MoveRotDegree;

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool GetIsLockOn() { return bIsLockOn; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetIsLockOn(bool LockOn) { bIsLockOn = LockOn; }

	FORCEINLINE int GetAttackCount() { return AttackCount; }
	FORCEINLINE void SetAttackCount(int _Count) { AttackCount = _Count; }
	FORCEINLINE bool GetGoNextAttack() { return GoNextAttack; }
	FORCEINLINE void SetGoNextAttack(bool NextAttack) { GoNextAttack = NextAttack; }
	FORCEINLINE bool GetCanTakeDown() { return bCanTakeDown; }
	FORCEINLINE void SetCanTakeDown(bool _TakeDown) { bCanTakeDown = _TakeDown; }

	FORCEINLINE ECharacterActionState GetCurActionState() { return CurActionState; }
	FORCEINLINE class UInventoryComponent* GetInventory() { return Inventory; }
	FORCEINLINE bool GetIsOpenItemExplain() { return IsOpenItemExplain; }
	FORCEINLINE void SetIsOpenItemExplain(bool _Set){ IsOpenItemExplain = _Set; }
	
	UFUNCTION(BlueprintCallable)
	void PushDoor();
	UFUNCTION(BlueprintCallable)
	void TurnOnLantern();
	UFUNCTION(BlueprintCallable)
	void LanternOn();
	UFUNCTION(BlueprintCallable)
	void SitComplete();
	UFUNCTION(BlueprintCallable)
	void SitDown();
	UFUNCTION(BlueprintCallable)
	void StandUp();
	UFUNCTION(BlueprintCallable)
	void PassFog();
	UFUNCTION(BlueprintCallable)
	void PassFogEnd();

	UFUNCTION(BlueprintCallable)
	void Kick();
	UFUNCTION(BlueprintCallable)
	void DoorSwitchOn();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit")
	class UParticleSystem* RegainEffect;
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
	void ItemSwap(const FInputActionValue& Value);
	void DeformWeapon(const FInputActionValue& Value);
	void OpenStatusInventory(const FInputActionValue& Value);
	void OpenQuickSlot(const FInputActionValue& Value);


	void TraceLockOnTarget(float DeltaTime);

	void ReleaseLockOn();
	void SetLockOn(class ABBAICharacter* Target);

	UFUNCTION(BlueprintCallable)
	void Deform();

	FString GetDeformMontageName();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UBBOverlay* BBOverlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UInventoryComponent* Inventory;

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

	UPROPERTY()
	bool IsOpenItemExplain = false;

	UPROPERTY(VisibleInstanceOnly)
	class AInteractObject* OverlappingObject;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TakeDown", meta = (AllowPrivateAccess = "true"))
	class AActor* TakeDownTarget;

	UPROPERTY(VisibleInstanceOnly, Category = "TakeDown")
	FVector TakeDownPos;

	UPROPERTY(VisibleInstanceOnly, Category = "TakeDown")
	FRotator TakeDownRot;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FVector InputVector = FVector::Zero();

public:
	void SetOverlappingObject(class AInteractObject* InteractObject) { OverlappingObject = InteractObject; }
	void SetTakeDownInfo(class AActor* Target, const FVector& Pos, const FRotator& Rot);
	void UpdateOverlay();

	UFUNCTION(BlueprintCallable)
	void Revive();
	UFUNCTION(BlueprintCallable)
	void Death();
	void DeathCheck();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsDeath = false;

	class UBBOverlay* GetBBOverlay() { return BBOverlay; }

	class AInteractObject* GetOverlappingObject() { return OverlappingObject; }

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

	TArray<struct FInvenSlotData**> RightHandSlotData;
	TArray<struct FInvenSlotData**> LeftHandSlotData;
	TArray<struct FInvenSlotData**> UseItemSlotData;

	UPROPERTY(BlueprintReadWrite)
	FHunterStatus CurStatus = FHunterStatus();

	void WeaponSlotUpdate();
	void UseItemSlotUpdate();
	void PotionBulletUpdate();
	void DisplayGoldUpdate(float _DeltaTime);
	int GetPotionNum();
	int GetBulletNum();

	void Drink();
	void Throw();

	UFUNCTION(BlueprintCallable)
	void SpawnThrowObject();

	UFUNCTION(BlueprintCallable)
	void UseItem();

	UFUNCTION(BlueprintCallable)
	void Heal();

	UFUNCTION(BlueprintCallable)
	int GetCurDamage(int _Strength);

	UFUNCTION(BlueprintCallable)
	void StatusUpdate();

	UPROPERTY(EditAnywhere)
	float BaseHp = 400.f;

	UPROPERTY(EditAnywhere)
	float VitalityScale = 40.f;

	UPROPERTY(EditAnywhere)
	float BaseStamina = 250.f;

	UPROPERTY(EditAnywhere)
	float EnduranceScale = 25.f;

	UPROPERTY(EditAnywhere)
	float HealAmount = 50.f;

	UPROPERTY(EditAnywhere)
	float ExhaustTime = 2.f;

	UPROPERTY()
	float AccExhaustTime = 2.f;

	UPROPERTY()
	bool bExhaust = false;

	UPROPERTY()
	float BaseConsumeStamina = 50.f;

	UPROPERTY()
	float ConsumeStaminaAmount = 75.f;

	void StaminaUpdate(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	void ConsumeStamina();

	UPROPERTY(EditAnywhere)
	TMap<EWeapon, TSubclassOf<class AWeapon>> WeaponList;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 CurMeleeListNum = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 CurRangedListNum = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 CurUseItemListNum = 0;

	UPROPERTY()
	int32 MaxListNum = 3;
};
