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
	void ReceiveDamage(float DamageAmount);

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
	float Stamina = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxStamina = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsDeath;
		
};
