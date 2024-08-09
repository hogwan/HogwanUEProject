// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/BBStatusInventory.h"
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
#include "ActorComponent/InventoryComponent.h"
#include "HUD/BBQuickSlot.h"
#include "ActorComponent/AttributeComponent.h"
#include "Weapon/MeleeWeapon.h"
#include "Kismet/GameplayStatics.h"

UBBStatusInventory::UBBStatusInventory()
{

}

void UBBStatusInventory::Init()
{
	RowSize = 3;
	ColumnSize = 4;

	Super::Init();
}

void UBBStatusInventory::Enter()
{
	Super::Enter();

	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
	ABBPlayerController* PlayerController = GameIns->BBPlayerController;
	ABBHUD* BBHUD = GameIns->HUD;
	AHunter* Hunter = GameIns->Hunter;

	FSelectedQuickSlotData QuickSlotData = BBHUD->QuickSlotData;

	FInvenSlotData& InvenData = Hunter->GetInventory()->Inventory[ColumnSize * Row + Column];

	if (QuickSlotData.IsQuickSlotSetting)
	{
		if (QuickSlotData.SelectedItemType == InvenData.ItemType)
		{
			for (int i = 0; i < Hunter->GetInventory()->QuickSlot.Num(); i++)
			{
				if (Hunter->GetInventory()->QuickSlot[i] == &InvenData)  Hunter->GetInventory()->QuickSlot[i] = nullptr;
			}

			Hunter->GetInventory()->QuickSlot[QuickSlotData.SelectedQuickSlotRow * 3 + QuickSlotData.SelectedQuickSlotColumn] = &InvenData;

			PlayerController->OpenWidget(EInputMode::QuickSlot);

			BBHUD->QuickSlotData.IsQuickSlotSetting = false;
			BBHUD->GetBBQuickSlot()->WidgetUpdate();
			
			Hunter->PotionBulletUpdate();
			Hunter->UseItemSlotUpdate();

			if (GameIns->SoundMap[TEXT("UIEnter")])
			{
				UGameplayStatics::PlaySound2D(
					this,
					GameIns->SoundMap[TEXT("UIEnter")]
				);
			}
		}
	}
	else
	{
		BBHUD->QuickSlotData.IsQuickSlotSetting = false;
		PlayerController->CloseWidget();

		Hunter->PotionBulletUpdate();
		Hunter->UseItemSlotUpdate();

		if (GameIns->SoundMap[TEXT("UIEnter")])
		{
			UGameplayStatics::PlaySound2D(
				this,
				GameIns->SoundMap[TEXT("UIEnter")]
			);
		}
	}
}

void UBBStatusInventory::WidgetUpdate()
{
	Super::WidgetUpdate();

	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
	AHunter* Hunter = GameIns->Hunter;

	UInventoryComponent* Inven = Hunter->GetInventory();

	for (int i = 0; i < Inven->Inventory.Num(); i++)
	{
		UBBInventorySlot* InvenSlot = Cast<UBBInventorySlot>(GridSlots->GetAllChildren()[i]);
		if (Inven->Inventory[i].IsEmpty == false)
		{
			InvenSlot->Number->SetText(FText::FromString(FString::FromInt(Inven->Inventory[i].Number)));
			InvenSlot->Number->SetVisibility(ESlateVisibility::Visible);

			InvenSlot->Item->SetVisibility(ESlateVisibility::Visible);
			SetItemTexture(Inven->Inventory[i].Item, i);
		}
		else
		{
			InvenSlot->Item->SetVisibility(ESlateVisibility::Hidden);
			InvenSlot->Number->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	LevelStat->SetText(FText::FromString(FString::FromInt(Hunter->CurStatus.Level)));

	VitalityStat->SetText(FText::FromString(FString::FromInt(Hunter->CurStatus.Vitality)));

	EnduranceStat->SetText(FText::FromString(FString::FromInt(Hunter->CurStatus.Endurance)));

	StrengthStat->SetText(FText::FromString(FString::FromInt(Hunter->CurStatus.Strength)));

	int HunterMaxHp = Hunter->GetAttribute()->MaxHp;
	int HunterCurHp = Hunter->GetAttribute()->Hp;
	int HunterMaxStamina = Hunter->GetAttribute()->MaxStamina;
	int HunterCurStamina = Hunter->GetAttribute()->Stamina;
	int HunterDamage = Hunter->GetCurDamage(Hunter->CurStatus.Strength);

	FString StrHPStat = FString::Printf(TEXT("%d / %d"), HunterCurHp, HunterMaxHp);
	FString StrStaminaStat = FString::Printf(TEXT("%d / %d"), HunterCurStamina, HunterMaxStamina);

	HPStat->SetText(FText::FromString(StrHPStat));
	StaminaStat->SetText(FText::FromString(StrStaminaStat));
	DamageStat->SetText(FText::FromString(FString::FromInt(HunterDamage)));
}

void UBBStatusInventory::CloseWidget()
{
	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
	ABBPlayerController* PlayerController = GameIns->BBPlayerController;
	ABBHUD* BBHUD = GameIns->HUD;

	FSelectedQuickSlotData QuickSlotData = BBHUD->QuickSlotData;

	if (QuickSlotData.IsQuickSlotSetting)
	{
		PlayerController->OpenWidget(EInputMode::QuickSlot);
		QuickSlotData.IsQuickSlotSetting = false;

		UGameplayStatics::PlaySound2D(
			this,
			GameIns->SoundMap["UIMenuClose"]
		);
	}
	else
	{
		PlayerController->CloseWidget();
	}


}

