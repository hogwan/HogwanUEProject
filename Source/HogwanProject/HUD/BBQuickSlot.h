// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/InputWidget.h"
#include "Global/BBEnum.h"
#include "BBQuickSlot.generated.h"

/**
 * 
 */
UCLASS()
class HOGWANPROJECT_API UBBQuickSlot : public UInputWidget
{
	GENERATED_BODY()
public:
	void Init() override;
	void Enter() override;
	void WidgetUpdate() override;

};
