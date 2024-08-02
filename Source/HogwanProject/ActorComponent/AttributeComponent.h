// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HOGWANPROJECT_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttributeComponent();

	UFUNCTION(BlueprintCallable)
	float GetHealthPercent();

	UFUNCTION(BlueprintCallable)
	float GetHunterMaxHealthPercent();

	UFUNCTION(BlueprintCallable)
	float GetHunterHealthPercent();

	UFUNCTION(BlueprintCallable)
	float GetHunterRegainHealthPercent();

	UFUNCTION(BlueprintCallable)
	float GetHunterMaxStaminaPercent();

	UFUNCTION(BlueprintCallable)
	float GetHunterStaminaPercent();

	UFUNCTION(BlueprintCallable)
	void ReceiveDamage(float DamageAmount);

	UFUNCTION(BlueprintCallable)
	void Heal(float HealAmount);

	UFUNCTION(BlueprintCallable)
	bool GetIsDeath();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Hp = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHp = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RegainHp = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RegainAmount = 30.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Stamina = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxStamina = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Limited = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsDeath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RegainTimeRemain = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RegainTime = 5.f;
		
};
