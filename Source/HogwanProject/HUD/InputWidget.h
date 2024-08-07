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
	virtual void Init();
	virtual void WidgetUpdate();

	UFUNCTION(BlueprintCallable)
	virtual void Enter();

	UFUNCTION(BlueprintCallable)
	virtual void MoveRight();
	UFUNCTION(BlueprintCallable)
	virtual void MoveLeft();
	UFUNCTION(BlueprintCallable)
	virtual void MoveUp();
	UFUNCTION(BlueprintCallable)
	virtual void MoveDown();
	UFUNCTION(BlueprintCallable)
	virtual void CloseWidget();
};
