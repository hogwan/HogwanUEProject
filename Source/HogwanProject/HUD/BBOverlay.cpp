// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/BBOverlay.h"
#include "Components/ProgressBar.h"

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
