// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemExplain.generated.h"

/**
 * 
 */
UCLASS()
class HOGWANPROJECT_API UItemExplain : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(meta = (BindWidget))
	class UImage* ItemExplainImage;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ItemExplainNum;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ItemExplainText;
};
