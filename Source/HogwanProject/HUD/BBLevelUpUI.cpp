// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/BBLevelUpUI.h"
#include "HUD/LevelUpUnit.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Character/Hunter/Hunter.h"
#include "Global/BBGameInstance.h"
#include "ActorComponent/AttributeComponent.h"

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

	WidgetUpdate();
}

void UBBLevelUpUI::WidgetUpdate()
{
	ExpectLevel->SetText(FText::FromString(FString::FromInt(ExpectLevelData)));
	ExpectGold->SetText(FText::FromString(FString::FromInt(ExpectGoldData)));
	ExpectHP->SetText(FText::FromString(FString::Printf(TEXT("%d / %d"),Hunter->GetAttribute()->Hp, ExpectHPData)));
	ExpectStamina->SetText(FText::FromString(FString::Printf(TEXT("%d / %d"), Hunter->GetAttribute()->Stamina,ExpectStaminaData)));
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
	Hunter->CurStatus.Strength = ExpectStaminaData;
}

void UBBLevelUpUI::MoveRight()
{
	switch (CurIndex)
	{
	case 0:



	case 1:
	case 2:

	}


	StatusDataUpdate();
	WidgetUpdate();
}

void UBBLevelUpUI::MoveLeft()
{
}

void UBBLevelUpUI::MoveUp()
{
}

void UBBLevelUpUI::MoveDown()
{
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
