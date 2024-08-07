// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/BBQuickSlot.h"
#include "Global/BBGameInstance.h"
#include "Character/Hunter/Hunter.h"
#include "ActorComponent/InventoryComponent.h"
#include "Components/UniformGridPanel.h"
#include "HUD/BBInventorySlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Character/Hunter/BBPlayerController.h"
#include "HUD/BBHUD.h"

void UBBQuickSlot::Init()
{
	RowSize = 3;
	ColumnSize = 3;

	Super::Init();
}

void UBBQuickSlot::Enter()
{
	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
	ABBHUD* BBHUD = GameIns->HUD;

	BBHUD->QuickSlotData.IsQuickSlotSetting = true;

	switch (Row)
	{
	case 0:
		BBHUD->QuickSlotData.SelectedItemType = EItemType::RightHandWeapon;
		break;
	case 1:
		BBHUD->QuickSlotData.SelectedItemType = EItemType::LeftHandWeapon;
		break;
	case 2:
		BBHUD->QuickSlotData.SelectedItemType = EItemType::UseItem;
		break;
	default:
		break;
	}

	BBHUD->QuickSlotData.SelectedQuickSlotColumn = Column;
	BBHUD->QuickSlotData.SelectedQuickSlotRow = Row;

	ABBPlayerController* PlayerController = GameIns->BBPlayerController;
	PlayerController->OpenWidget(EInputMode::StatusInventory);
}


void UBBQuickSlot::WidgetUpdate()
{
	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
	AHunter* Hunter = GameIns->Hunter;

	UInventoryComponent* Inven = Hunter->GetInventory();

	for (int i = 0; i < Inven->QuickSlot.Num(); i++)
	{
		UBBInventorySlot* InvenSlot = Cast<UBBInventorySlot>(GreedSlots->GetAllChildren()[i]);
		if (Inven->QuickSlot[i] != nullptr)
		{
			if (Inven->QuickSlot[i]->Number == 0)
			{
				Inven->QuickSlot[i] = nullptr;
				InvenSlot->Item->SetVisibility(ESlateVisibility::Hidden);
				InvenSlot->Number->SetVisibility(ESlateVisibility::Hidden);
				continue;
			}

			InvenSlot->Number->SetText(FText::FromString(FString::FromInt(Inven->QuickSlot[i]->Number)));
			InvenSlot->Number->SetVisibility(ESlateVisibility::Visible);

			InvenSlot->Item->SetVisibility(ESlateVisibility::Visible);
			SetItemTexture(Inven->QuickSlot[i]->Item, i);
		}
		else
		{
			InvenSlot->Item->SetVisibility(ESlateVisibility::Hidden);
			InvenSlot->Number->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	Hunter->WeaponSlotUpdate();
}
