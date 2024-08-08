// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/InputWidget.h"
#include "BBLevelUpUI.generated.h"

/**
 * 
 */
UCLASS()
class HOGWANPROJECT_API UBBLevelUpUI : public UInputWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class ULevelUpUnit*> LevelUpUnits;
	
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class ULevelUpUnit* Vitality;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class ULevelUpUnit* Endurance;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class ULevelUpUnit* Strength;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ExpectLevel;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ExpectGold;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ExpectHP;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ExpectStamina;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ExpectDamage;

	int ExpectLevelData = 0;
	int ExpectGoldData = 0;
	int ExpectHPData = 0;
	int ExpectStaminaData = 0;
	int ExpectDamageData = 0;
	int ExpectVitalityData = 0;
	int ExpectEnduranceData = 0;
	int ExpectStrengthData = 0;


	virtual void Init();
	virtual void WidgetUpdate();
	void StatusDataUpdate();

	virtual void Enter();

	virtual void MoveRight();
	virtual void MoveLeft();
	virtual void MoveUp();
	virtual void MoveDown();

	void Focus(int Index);
	void FocusEnd(int Index);

	UPROPERTY(BlueprintReadWrite)
	class AHunter* Hunter = nullptr;

	int CurIndex = 0;
};
