// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BBOverlay.generated.h"

/**
 * 
 */
UCLASS()
class HOGWANPROJECT_API UBBOverlay : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* MaxHealthBar;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* RegainHealthBar;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* MaxStaminaBar;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* StaminaBar;

	UPROPERTY(meta = (BindWidget))
	class UImage* EquippedUseItem;

	UPROPERTY(meta = (BindWidget))
	class UImage* EquippedRangedWeapon;

	UPROPERTY(meta = (BindWidget))
	class UImage* EquippedMeleeWeapon;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PotionNum;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* BulletNum;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ItemNum;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ItemInteractText;

	UPROPERTY(meta = (BindWidget))
	class UItemExplain* ItemExplain;
	
	void SetHealthBarPercent(float Percent);
	void SetMaxHealthBarPercent(float Percent);
	void SetRegainHealthBarPercent(float Percent);

	void SetStaminaBarPercent(float Percent);
	void SetMaxStaminaBarPerent(float Percent);

	void SetUseItemImage(UTexture2D* Tex);
	void SetRangedWeaponImage(UTexture2D* Tex);
	void SetMeleeWeaponImage(UTexture2D* Tex);
	void SetPotionNum(int Num);
	void SetBulletNum(int Num);

	
};
