// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Global/BBEnum.h"
#include "InputWidget.generated.h"

/**
 * 
 */
UCLASS()
class HOGWANPROJECT_API UInputWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel* GreedSlots;

	UPROPERTY()
	int Row;

	UPROPERTY()
	int Column;

	UPROPERTY()
	int RowSize;
	
	UPROPERTY()
	int ColumnSize;

	virtual void Init();
	virtual void WidgetUpdate();

	UFUNCTION(BlueprintCallable)
	virtual void Enter();

	UFUNCTION(BlueprintCallable)
	void MoveRight();
	UFUNCTION(BlueprintCallable)
	void MoveLeft();
	UFUNCTION(BlueprintCallable)
	void MoveUp();
	UFUNCTION(BlueprintCallable)
	void MoveDown();
	UFUNCTION(BlueprintCallable)
	virtual void CloseWidget();

	void Focus(int _Row, int _Column);
	void FocusEnd(int _Row, int _Column);

	void AddColumn();
	void SubColumn();
	void AddRow();
	void SubRow();

	void SetItemTexture(EItem _Item, int _Index);
};
