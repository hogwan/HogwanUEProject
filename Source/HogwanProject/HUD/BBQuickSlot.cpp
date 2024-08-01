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

void UBBQuickSlot::Init()
{
	Row = 0;
	Column = 0;

	for (UWidget* IvSlot : QuickSlots->GetAllChildren())
	{
		UBBInventorySlot* InvenSlot = Cast<UBBInventorySlot>(IvSlot);

		InvenSlot->Selected->SetRenderOpacity(0.f);
	}

	Focus(Row, Column);
}

void UBBQuickSlot::MoveRight()
{
	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
	AHunter* Hunter = GameIns->Hunter;

	UInventoryComponent* Inven = Hunter->GetInventory();

	if (11 == 3 * Row + Column) return;

	FocusEnd(Row, Column);

	AddColumn();

	Focus(Row, Column);

}

void UBBQuickSlot::MoveLeft()
{
	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
	AHunter* Hunter = GameIns->Hunter;

	UInventoryComponent* Inven = Hunter->GetInventory();

	if (0 == 3 * Row + Column) return;

	FocusEnd(Row, Column);

	SubColumn();

	Focus(Row, Column);
}

void UBBQuickSlot::MoveUp()
{
	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
	AHunter* Hunter = GameIns->Hunter;

	UInventoryComponent* Inven = Hunter->GetInventory();

	if (0 == Row) return;

	FocusEnd(Row, Column);

	SubRow();

	Focus(Row, Column);
}

void UBBQuickSlot::MoveDown()
{
	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
	AHunter* Hunter = GameIns->Hunter;

	UInventoryComponent* Inven = Hunter->GetInventory();

	if (2 == Row) return;

	FocusEnd(Row, Column);

	AddRow();

	Focus(Row, Column);
}

void UBBQuickSlot::Enter()
{
	
}

void UBBQuickSlot::Focus(int _Row, int _Column)
{
	UBBInventorySlot* InvenSlot = Cast<UBBInventorySlot>(QuickSlots->GetAllChildren()[3 * _Row + _Column]);
	InvenSlot->Selected->SetRenderOpacity(1.f);
}

void UBBQuickSlot::FocusEnd(int _Row, int _Column)
{
	UBBInventorySlot* InvenSlot = Cast<UBBInventorySlot>(QuickSlots->GetAllChildren()[3 * _Row + _Column]);
	InvenSlot->Selected->SetRenderOpacity(0.f);
}

void UBBQuickSlot::AddColumn()
{
	Column++;
	if (Column >= 3)
	{
		Row++;
		Column -= 3;
	}
}

void UBBQuickSlot::SubColumn()
{
	Column--;
	if (Column <= -1)
	{
		Row--;
		Column += 3;
	}
}

void UBBQuickSlot::AddRow()
{
	Row++;
}

void UBBQuickSlot::SubRow()
{
	Row--;
}

void UBBQuickSlot::UpdateQuickSlot()
{
	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
	AHunter* Hunter = GameIns->Hunter;

	UInventoryComponent* Inven = Hunter->GetInventory();

	for (int i = 0; i < Inven->QuickSlot.Num(); i++)
	{
		UBBInventorySlot* InvenSlot = Cast<UBBInventorySlot>(QuickSlots->GetAllChildren()[i]);
		if (Inven->QuickSlot[i].IsEmpty == false)
		{
			InvenSlot->Number->SetText(FText::FromString(FString::FromInt(Inven->QuickSlot[i].Number)));

			InvenSlot->Item->SetVisibility(ESlateVisibility::Visible);
			SetItemTexture(Inven->QuickSlot[i].Item, i);
		}
		else
		{
			InvenSlot->Item->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UBBQuickSlot::CloseQuickSlot()
{
	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
	ABBPlayerController* PlayerController = GameIns->BBPlayerController;
	PlayerController->CloseQuickSlot();
}

void UBBQuickSlot::SetItemTexture(EItem _Item, int _Index)
{
	UBBInventorySlot* InvenSlot = Cast<UBBInventorySlot>(QuickSlots->GetAllChildren()[_Index]);
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