// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/BBLevelUpUI.h"
#include "HUD/LevelUpUnit.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Character/Hunter/Hunter.h"
#include "Global/BBGameInstance.h"
#include "ActorComponent/AttributeComponent.h"
#include "Character/Hunter/BBPlayerController.h"

void UBBLevelUpUI::Init()
{
	if (Hunter == nullptr)
	{
		UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
		Hunter = GameIns->Hunter;
	}

	ExpectLevelData = Hunter->CurStatus.Level;
	ExpectGoldData = Hunter->CurStatus.Gold;
	ExpectHPData = Hunter->BaseHp + Hunter->CurStatus.Vitality * Hunter->VitalityScale;
	ExpectStaminaData = Hunter->BaseStamina + Hunter->CurStatus.Endurance * Hunter->EnduranceScale;
	ExpectDamageData = Hunter->GetCurDamage(Hunter->CurStatus.Strength);
	ExpectVitalityData = Hunter->CurStatus.Vitality;
	ExpectEnduranceData = Hunter->CurStatus.Endurance;
	ExpectStrengthData = Hunter->CurStatus.Strength;
	ExpectGoldData = Hunter->CurStatus.Gold;

	CurIndex = 0;
	Focus(CurIndex);
	FocusEnd(1);
	FocusEnd(2);

	StatusDataUpdate();
	WidgetUpdate();
}

void UBBLevelUpUI::WidgetUpdate()
{
	ExpectLevel->SetText(FText::FromString(FString::FromInt(ExpectLevelData)));
	ExpectGold->SetText(FText::FromString(FString::FromInt(ExpectGoldData)));
	ExpectHP->SetText(FText::FromString(FString::Printf(TEXT("%d / %d"),static_cast<int>(Hunter->GetAttribute()->Hp), ExpectHPData)));
	ExpectStamina->SetText(FText::FromString(FString::Printf(TEXT("%d / %d"), static_cast<int>(Hunter->GetAttribute()->Stamina),ExpectStaminaData)));
	ExpectDamage->SetText(FText::FromString(FString::FromInt(ExpectDamageData)));
	Vitality->ExpectStat->SetText(FText::FromString(FString::FromInt(ExpectVitalityData)));
	Endurance->ExpectStat->SetText(FText::FromString(FString::FromInt(ExpectEnduranceData)));
	Strength->ExpectStat->SetText(FText::FromString(FString::FromInt(ExpectStrengthData)));
}

void UBBLevelUpUI::StatusDataUpdate()
{
	ExpectHPData = Hunter->BaseHp + ExpectVitalityData * Hunter->VitalityScale;
	ExpectStaminaData = Hunter->BaseStamina + ExpectEnduranceData * Hunter->EnduranceScale;
	ExpectDamageData = Hunter->GetCurDamage(ExpectStrengthData);
}

void UBBLevelUpUI::Enter()
{
	Hunter->CurStatus.Level = ExpectLevelData;
	Hunter->CurStatus.Gold = ExpectGoldData;
	Hunter->CurStatus.Vitality = ExpectVitalityData;
	Hunter->CurStatus.Endurance = ExpectEnduranceData;
	Hunter->CurStatus.Strength = ExpectStrengthData;
	Hunter->StatusUpdate();

	CloseWidget();
}

void UBBLevelUpUI::CloseWidget()
{
	Super::CloseWidget();

	Hunter->StandUp();
}

void UBBLevelUpUI::MoveRight()
{
	if (ExpectGoldData < Cost) return;
	ExpectGoldData -= Cost;

	switch (CurIndex)
	{
	case 0:
		ExpectVitalityData++;
		break;
	case 1:
		ExpectEnduranceData++;
		break;
	case 2:
		ExpectStrengthData++;
		break;
	}

	ExpectLevelData++;
	StatusDataUpdate();
	WidgetUpdate();
}

void UBBLevelUpUI::MoveLeft()
{
	switch (CurIndex)
	{
	case 0:
	{
		if (ExpectVitalityData == 0 || ExpectVitalityData == Hunter->CurStatus.Vitality)
		{
			return;
		}

		ExpectVitalityData--;
		break;
	}
	case 1:
		if (ExpectEnduranceData == 0 || ExpectEnduranceData == Hunter->CurStatus.Endurance)
		{
			return;
		}
		ExpectEnduranceData--;
		break;
	case 2:
		if (ExpectStrengthData == 0 || ExpectStrengthData == Hunter->CurStatus.Strength)
		{
			return;
		}
		ExpectStrengthData--;
		break;
	}

	ExpectGoldData += Cost;
	ExpectLevelData--;
	StatusDataUpdate();
	WidgetUpdate();
}

void UBBLevelUpUI::MoveUp()
{
	if (CurIndex == 0) return;

	FocusEnd(CurIndex);

	CurIndex--;

	Focus(CurIndex);
}

void UBBLevelUpUI::MoveDown()
{
	if (CurIndex == 2) return;

	FocusEnd(CurIndex);

	CurIndex++;

	Focus(CurIndex);
}

void UBBLevelUpUI::Focus(int Index)
{
	LevelUpUnits[Index]->LeftArrow->SetVisibility(ESlateVisibility::Visible);
	LevelUpUnits[Index]->RightArrow->SetVisibility(ESlateVisibility::Visible);
}

void UBBLevelUpUI::FocusEnd(int Index)
{
	LevelUpUnits[Index]->LeftArrow->SetVisibility(ESlateVisibility::Hidden);
	LevelUpUnits[Index]->RightArrow->SetVisibility(ESlateVisibility::Hidden);
}
