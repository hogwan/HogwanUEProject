// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BBStatusInventory.generated.h"

/**
 * 
 */
UCLASS()
class HOGWANPROJECT_API UBBStatusInventory : public UUserWidget
{
	GENERATED_BODY()

public:
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

	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel* InventorySlots;

	
};
