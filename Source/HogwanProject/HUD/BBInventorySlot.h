// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BBInventorySlot.generated.h"

/**
 * 
 */
UCLASS()
class HOGWANPROJECT_API UBBInventorySlot : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	class UImage* BackGround;

	UPROPERTY(meta = (BindWidget))
	class UImage* Selected;

	UPROPERTY(meta = (BindWidget))
	class UImage* Item;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Number;
};
