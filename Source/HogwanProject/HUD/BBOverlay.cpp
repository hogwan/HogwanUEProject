// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/BBOverlay.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void UBBOverlay::SetHealthBarPercent(float Percent)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(Percent);
	}
}

void UBBOverlay::SetMaxHealthBarPercent(float Percent)
{
	if (MaxHealthBar)
	{
		MaxHealthBar->SetPercent(Percent);
	}
}

void UBBOverlay::SetRegainHealthBarPercent(float Percent)
{
	if (RegainHealthBar)
	{
		RegainHealthBar->SetPercent(Percent);
	}
}

void UBBOverlay::SetStaminaBarPercent(float Percent)
{
	if (StaminaBar)
	{
		StaminaBar->SetPercent(Percent);
	}
}

void UBBOverlay::SetMaxStaminaBarPerent(float Percent)
{
	if (MaxStaminaBar)
	{
		MaxStaminaBar->SetPercent(Percent);
	}
}

void UBBOverlay::SetUseItemImage(UTexture2D* Tex)
{
	UWidgetBlueprintLibrary::SetBrushResourceToTexture(EquippedUseItem->Brush, Tex);

	if (Tex == nullptr)
	{
		EquippedUseItem->SetRenderOpacity(0.f);
	}
	else
	{
		EquippedUseItem->SetRenderOpacity(1.f);
	}
}

void UBBOverlay::SetRangedWeaponImage(UTexture2D* Tex)
{
	UWidgetBlueprintLibrary::SetBrushResourceToTexture(EquippedRangedWeapon->Brush, Tex);

	if (Tex == nullptr)
	{
		EquippedRangedWeapon->SetRenderOpacity(0.f);
	}
	else
	{
		EquippedRangedWeapon->SetRenderOpacity(1.f);
	}
}

void UBBOverlay::SetMeleeWeaponImage(UTexture2D* Tex)
{
	UWidgetBlueprintLibrary::SetBrushResourceToTexture(EquippedMeleeWeapon->Brush, Tex);

	if (Tex == nullptr)
	{
		EquippedMeleeWeapon->SetRenderOpacity(0.f);
	}
	else
	{
		EquippedMeleeWeapon->SetRenderOpacity(1.f);
	}
}

void UBBOverlay::SetPotionNum(int Num)
{
	PotionNum->SetText(FText::FromString(FString::FromInt(Num)));
}

void UBBOverlay::SetBulletNum(int Num)
{
	BulletNum->SetText(FText::FromString(FString::FromInt(Num)));
}
