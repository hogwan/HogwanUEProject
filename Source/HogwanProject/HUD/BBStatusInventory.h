// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Global/BBEnum.h"
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

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Row;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Column;

	UFUNCTION(BlueprintCallable)
	void Init();

	UFUNCTION(BlueprintCallable)
	void MoveRight();

	UFUNCTION(BlueprintCallable)
	void MoveLeft();

	UFUNCTION(BlueprintCallable)
	void MoveUp();

	UFUNCTION(BlueprintCallable)
	void MoveDown();

	UFUNCTION(BlueprintCallable)
	void Enter();

	UFUNCTION(BlueprintCallable)
	void Focus(int _Row, int _Column);

	UFUNCTION(BlueprintCallable)
	void FocusEnd(int _Row, int _Column);

	void AddColumn();
	void SubColumn();
	void AddRow();
	void SubRow();

	void UpdateInventory();
	void SetItemTexture(EItem _Item, int _Index);
};
