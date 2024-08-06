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

void UBBStatusInventory::Init()
{
	Row = 0;
	Column = 0;

	for (UWidget* IvSlot : InventorySlots->GetAllChildren())
	{
		UBBInventorySlot* InvenSlot = Cast<UBBInventorySlot>(IvSlot);

		InvenSlot->Selected->SetRenderOpacity(0.f);
	}

	Focus(Row, Column);
}

void UBBStatusInventory::MoveRight()
{
	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
	AHunter* Hunter = GameIns->Hunter;

	UInventoryComponent* Inven = Hunter->GetInventory();

	if (11 == 4 * Row + Column) return;

	FocusEnd(Row, Column);

	AddColumn();

	Focus(Row, Column);
	
}

void UBBStatusInventory::MoveLeft()
{
	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
	AHunter* Hunter = GameIns->Hunter;

	UInventoryComponent* Inven = Hunter->GetInventory();

	if (0 == 4 * Row + Column) return;

	FocusEnd(Row, Column);

	SubColumn();

	Focus(Row, Column);
}

void UBBStatusInventory::MoveUp()
{
	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
	AHunter* Hunter = GameIns->Hunter;

	UInventoryComponent* Inven = Hunter->GetInventory();

	if (0 == Row) return;

	FocusEnd(Row, Column);

	SubRow();

	Focus(Row, Column);
}

void UBBStatusInventory::MoveDown()
{
	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
	AHunter* Hunter = GameIns->Hunter;

	UInventoryComponent* Inven = Hunter->GetInventory();

	if (2 == Row) return;

	FocusEnd(Row, Column);

	AddRow();

	Focus(Row, Column);
}

void UBBStatusInventory::Enter()
{
	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
	ABBPlayerController* PlayerController = GameIns->BBPlayerController;
	ABBHUD* BBHUD = GameIns->HUD;
	AHunter* Hunter = GameIns->Hunter;

	FSelectedQuickSlotData QuickSlotData = BBHUD->QuickSlotData;

	FInvenSlotData& InvenData = Hunter->GetInventory()->Inventory[4 * Row + Column];

	if (QuickSlotData.IsQuickSlotSetting)
	{
		if (QuickSlotData.SelectedItemType == InvenData.ItemType)
		{
			for (int i = 0; i < Hunter->GetInventory()->QuickSlot.Num(); i++)
			{
				if (Hunter->GetInventory()->QuickSlot[i] == &InvenData)  Hunter->GetInventory()->QuickSlot[i] = nullptr;
			}

			Hunter->GetInventory()->QuickSlot[QuickSlotData.SelectedQuickSlotRow * 3 + QuickSlotData.SelectedQuickSlotColumn] = &InvenData;

			PlayerController->CloseStatusInventory();

			BBHUD->QuickSlotData.IsQuickSlotSetting = false;
			BBHUD->GetBBQuickSlot()->UpdateQuickSlot();
			
			Hunter->PotionBulletUpdate();
			Hunter->UseItemSlotUpdate();
		}
	}
	else
	{
		if (InvenData.ItemType == EItemType::UseItem)
		{
			Hunter->Throw();
			BBHUD->GetBBQuickSlot()->UpdateQuickSlot();
		}

		BBHUD->QuickSlotData.IsQuickSlotSetting = false;
		PlayerController->CloseStatusInventory();

		Hunter->PotionBulletUpdate();
		Hunter->UseItemSlotUpdate();
	}
}

void UBBStatusInventory::Focus(int _Row, int _Column)
{
	UBBInventorySlot* InvenSlot = Cast<UBBInventorySlot>(InventorySlots->GetAllChildren()[4 * _Row + _Column]);
	InvenSlot->Selected->SetRenderOpacity(1.f);
}

void UBBStatusInventory::FocusEnd(int _Row, int _Column)
{
	UBBInventorySlot* InvenSlot = Cast<UBBInventorySlot>(InventorySlots->GetAllChildren()[4 * _Row + _Column]);
	InvenSlot->Selected->SetRenderOpacity(0.f);
}

void UBBStatusInventory::AddColumn()
{
	Column++;
	if (Column >= 4)
	{
		Row++;
		Column -= 4;
	}
}

void UBBStatusInventory::SubColumn()
{
	Column--;
	if (Column <= -1)
	{
		Row--;
		Column += 4;
	}
}

void UBBStatusInventory::AddRow()
{
	Row++;
}

void UBBStatusInventory::SubRow()
{
	Row--;
}

void UBBStatusInventory::UpdateInventory()
{
	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
	AHunter* Hunter = GameIns->Hunter;

	UInventoryComponent* Inven = Hunter->GetInventory();

	for (int i = 0; i < Inven->Inventory.Num(); i++)
	{
		UBBInventorySlot* InvenSlot = Cast<UBBInventorySlot>(InventorySlots->GetAllChildren()[i]);
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
	int HunterDamage = Hunter->GetCurDamage();

	FString StrHPStat = FString::Printf(TEXT("%d / %d"), HunterCurHp, HunterMaxHp);
	FString StrStaminaStat = FString::Printf(TEXT("%d / %d"), HunterCurStamina, HunterMaxStamina);

	HPStat->SetText(FText::FromString(StrHPStat));
	StaminaStat->SetText(FText::FromString(StrStaminaStat));
	DamageStat->SetText(FText::FromString(FString::FromInt(HunterDamage)));
}

void UBBStatusInventory::CloseStatusInventory()
{
	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
	ABBPlayerController* PlayerController = GameIns->BBPlayerController;
	PlayerController->CloseStatusInventory();
}

void UBBStatusInventory::SetItemTexture(EItem _Item, int _Index)
{
	UBBInventorySlot* InvenSlot = Cast<UBBInventorySlot>(InventorySlots->GetAllChildren()[_Index]);
	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());

	switch (_Item)
	{
	case EItem::None:
		UWidgetBlueprintLibrary::SetBrushResourceToTexture(InvenSlot->Item->Brush, nullptr);
		break;
	case EItem::GreatSword:
		UWidgetBlueprintLibrary::SetBrushResourceToTexture(InvenSlot->Item->Brush, GameIns->TextureMap["GreatSword"]);
		break;
	case EItem::Katana:
		UWidgetBlueprintLibrary::SetBrushResourceToTexture(InvenSlot->Item->Brush, GameIns->TextureMap["Katana"]);
		break;
	case EItem::SawCleaver:
		UWidgetBlueprintLibrary::SetBrushResourceToTexture(InvenSlot->Item->Brush, GameIns->TextureMap["SawCleaver"]);
		break;
	case EItem::HunterPistol:
		UWidgetBlueprintLibrary::SetBrushResourceToTexture(InvenSlot->Item->Brush, GameIns->TextureMap["HunterPistol"]);
		break;
	case EItem::Bullet:
		UWidgetBlueprintLibrary::SetBrushResourceToTexture(InvenSlot->Item->Brush, GameIns->TextureMap["Bullet"]);
		break;
	case EItem::FireBottle:
		UWidgetBlueprintLibrary::SetBrushResourceToTexture(InvenSlot->Item->Brush, GameIns->TextureMap["FireBottle"]);
		break;
	case EItem::Potion:
		UWidgetBlueprintLibrary::SetBrushResourceToTexture(InvenSlot->Item->Brush, GameIns->TextureMap["Potion"]);
		break;
	case EItem::Stone:
		UWidgetBlueprintLibrary::SetBrushResourceToTexture(InvenSlot->Item->Brush, GameIns->TextureMap["Stone"]);
		break;
	default:
		break;
	}
}

