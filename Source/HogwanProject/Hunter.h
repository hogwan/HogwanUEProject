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

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool GetIsLockOn() { return bLockOn; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetIsLockOn(bool LockOn) { bLockOn = LockOn; }

protected:
	virtual void BeginPlay() override;

private:
	//  Components
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* ViewCamera;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Run(const FInputActionValue& Value);
	void Dodge(const FInputActionValue& Value);

	bool bIsRun = false;
	bool bLockOn = false;
};
