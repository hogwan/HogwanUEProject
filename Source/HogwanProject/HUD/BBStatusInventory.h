// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/InputWidget.h"
#include "Global/BBEnum.h"
#include "BBStatusInventory.generated.h"

/**
 * 
 */
UCLASS()
class HOGWANPROJECT_API UBBStatusInventory : public UInputWidget
{
	GENERATED_BODY()

public:
	UBBStatusInventory();

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* LevelStat;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* VitalityStat;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* EnduranceStat;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* StrengthStat;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* HPStat;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* StaminaStat;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DamageStat;

	void Init() override;
	void Enter() override;
	void WidgetUpdate() override;
	void CloseWidget() override;
};
