// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/GridInputWidget.h"
#include "HUD/BBInventorySlot.h"
#include "Components/UniformGridPanel.h"
#include "Components/Image.h"
#include "Global/BBGameInstance.h"
#include "Character/Hunter/BBPlayerController.h"
#include "Blueprint/WidgetBlueprintLibrary.h"


void UGridInputWidget::Init()
{
	Super::Init();
	Row = 0;
	Column = 0;

	for (UWidget* IvSlot : GridSlots->GetAllChildren())
	{
		UBBInventorySlot* InvenSlot = Cast<UBBInventorySlot>(IvSlot);

		InvenSlot->Selected->SetRenderOpacity(0.f);
	}

	Focus(Row, Column);
}

void UGridInputWidget::Enter()
{
	Super::Enter();
}

void UGridInputWidget::WidgetUpdate()
{
	Super::WidgetUpdate();
}

void UGridInputWidget::MoveRight()
{
	Super::MoveRight();

	if ((ColumnSize * RowSize - 1) == ColumnSize * Row + Column) return;

	FocusEnd(Row, Column);

	AddColumn();

	Focus(Row, Column);
}

void UGridInputWidget::MoveLeft()
{
	Super::MoveLeft();

	if (0 == ColumnSize * Row + Column) return;

	FocusEnd(Row, Column);

	SubColumn();

	Focus(Row, Column);
}

void UGridInputWidget::MoveUp()
{
	Super::MoveUp();

	if (0 == Row) return;

	FocusEnd(Row, Column);

	SubRow();

	Focus(Row, Column);
}

void UGridInputWidget::MoveDown()
{
	Super::MoveDown();

	if (RowSize - 1 == Row) return;

	FocusEnd(Row, Column);

	AddRow();

	Focus(Row, Column);
}

void UGridInputWidget::CloseWidget()
{
	Super::CloseWidget();
}



void UGridInputWidget::Focus(int _Row, int _Column)
{
	UBBInventorySlot* InvenSlot = Cast<UBBInventorySlot>(GridSlots->GetAllChildren()[ColumnSize * _Row + _Column]);
	InvenSlot->Selected->SetRenderOpacity(1.f);
}

void UGridInputWidget::FocusEnd(int _Row, int _Column)
{
	UBBInventorySlot* InvenSlot = Cast<UBBInventorySlot>(GridSlots->GetAllChildren()[ColumnSize * _Row + _Column]);
	InvenSlot->Selected->SetRenderOpacity(0.f);
}

void UGridInputWidget::AddColumn()
{
	Column++;
	if (Column >= ColumnSize)
	{
		Row++;
		Column -= ColumnSize;
	}
}

void UGridInputWidget::SubColumn()
{
	Column--;
	if (Column <= -1)
	{
		Row--;
		Column += ColumnSize;
	}
}

void UGridInputWidget::AddRow()
{
	Row++;
}

void UGridInputWidget::SubRow()
{
	Row--;
}

void UGridInputWidget::SetItemTexture(EItem _Item, int _Index)
{
	UBBInventorySlot* InvenSlot = Cast<UBBInventorySlot>(GridSlots->GetAllChildren()[_Index]);
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
