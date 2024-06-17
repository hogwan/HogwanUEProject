// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float MoveRotDegree;

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool GetIsLockOn() { return bIsLockOn; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetIsLockOn(bool LockOn) { bIsLockOn = LockOn; }

	

protected:
	virtual void BeginPlay() override;

private:
	//  Components
	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* ViewCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class AActor* LockOnTarget;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Run(const FInputActionValue& Value);
	void Dodge(const FInputActionValue& Value);
	void LockOn(const FInputActionValue& Value);

	void TraceLockOnTarget(float DeltaTime);

	bool bIsRun = false;
	bool bIsLockOn = false;
};
