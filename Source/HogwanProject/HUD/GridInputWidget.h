// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/InputWidget.h"
#include "GridInputWidget.generated.h"

/**
 * 
 */
UCLASS()
class HOGWANPROJECT_API UGridInputWidget : public UInputWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel* GridSlots;

	UPROPERTY()
	int Row;

	UPROPERTY()
	int Column;

	UPROPERTY()
	int RowSize;

	UPROPERTY()
	int ColumnSize;

	void Focus(int _Row, int _Column);
	void FocusEnd(int _Row, int _Column);

	void AddColumn();
	void SubColumn();
	void AddRow();
	void SubRow();

	virtual void Init() override;

	virtual void WidgetUpdate() override;

	virtual void Enter() override;

	virtual void MoveRight() override;

	virtual void MoveLeft() override;

	virtual void MoveUp() override;

	virtual void MoveDown() override;

	virtual void CloseWidget() override;

	void SetItemTexture(EItem _Item, int _Index);

};
