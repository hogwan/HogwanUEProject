// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LevelUpUnit.generated.h"

/**
 * 
 */
UCLASS()
class HOGWANPROJECT_API ULevelUpUnit : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ExpectStat;

	UPROPERTY(meta = (BindWidget))
	class UImage* LeftArrow;

	UPROPERTY(meta = (BindWidget))
	class UImage* RightArrow;
};
