// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BBOverlay.generated.h"

/**
 * 
 */
UCLASS()
class HOGWANPROJECT_API UBBOverlay : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* MaxHealthBar;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* RegainHealthBar;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* MaxStaminaBar;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* StaminaBar;
	
	void SetHealthBarPercent(float Percent);
	void SetMaxHealthBarPercent(float Percent);
	void SetRegainHealthBarPercent(float Percent);

	void SetStaminaBarPercent(float Percent);
	void SetMaxStaminaBarPerent(float Percent);

	
};
