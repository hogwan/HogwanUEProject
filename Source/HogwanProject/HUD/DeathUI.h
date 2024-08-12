// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/InputWidget.h"
#include "DeathUI.generated.h"

/**
 * 
 */
UCLASS()
class HOGWANPROJECT_API UDeathUI : public UInputWidget
{
	GENERATED_BODY()
	
public:
	void Enter() override;
	void CloseWidget() override;
};
