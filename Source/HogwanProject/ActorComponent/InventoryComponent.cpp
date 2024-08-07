// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponent/InventoryComponent.h"
#include "Tool/Item/Item.h"
#include "Global/BBGameInstance.h"
#include "HUD/BBStatusInventory.h"
#include "HUD/BBHUD.h"
#include "Character/Hunter/Hunter.h"
#include "HUD/BBQuickSlot.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;


}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < 12; i++)
	{
		FInvenSlotData ItemSlotInfo;
		ItemSlotInfo.Index = i;
		Inventory.Add(ItemSlotInfo);
	}

	for (int i = 0; i < 9; i++)
	{
		QuickSlot.Add(nullptr);
	}

	AHunter* Hunter = Cast<AHunter>(GetOwner());
	Hunter->RightHandSlotData[0] = &QuickSlot[0];
	Hunter->RightHandSlotData[1] = &QuickSlot[1];
	Hunter->RightHandSlotData[2] = &QuickSlot[2];

	Hunter->LeftHandSlotData[0] = &QuickSlot[3];
	Hunter->LeftHandSlotData[1] = &QuickSlot[4];
	Hunter->LeftHandSlotData[2] = &QuickSlot[5];

	Hunter->UseItemSlotData[0] = &QuickSlot[6];
	Hunter->UseItemSlotData[1] = &QuickSlot[7];
	Hunter->UseItemSlotData[2] = &QuickSlot[8];

}

void UInventoryComponent::PickUpItem(AItem* _PickUpItem)
{
	int ItemNum = _PickUpItem->GetItemNum();
	EItem Item = _PickUpItem->GetItem();
	EItemType ItemType = _PickUpItem->GetItemType();
	EWeapon Weapon = _PickUpItem->GetWeapon();

	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetOwner()->GetGameInstance());
	ABBHUD* BBHUD = GameIns->HUD;

	for (int i = 0; i < Inventory.Num(); i++)
	{
		EItem SlotItem = Inventory[i].Item;
		bool IsEmpty = Inventory[i].IsEmpty;

		if (SlotItem == Item)
		{
			Inventory[i].Number += ItemNum;
			BBHUD->GetBBStatusInventory()->WidgetUpdate();
			BBHUD->GetBBQuickSlot()->WidgetUpdate();
			return;
		}

		if (IsEmpty)
		{
			FInvenSlotData TempItemSlotInfo;
			TempItemSlotInfo.IsEmpty = false;
			TempItemSlotInfo.Number = ItemNum;
			TempItemSlotInfo.Item = Item;
			TempItemSlotInfo.ItemType = ItemType;
			TempItemSlotInfo.Weapon = Weapon;
			TempItemSlotInfo.Index = i;
			Inventory[i] = TempItemSlotInfo;
			break;
		}
	}

	BBHUD->GetBBStatusInventory()->WidgetUpdate();
	BBHUD->GetBBQuickSlot()->WidgetUpdate();
}

void UInventoryComponent::UseItem(int InventoryIndex)
{
	EItemType ItemType = Inventory[InventoryIndex].ItemType;

	if (ItemType != EItemType::UseItem) return;

	if (Inventory[InventoryIndex].Number <= 1)
	{
		FInvenSlotData ItemSlotInfo;
		ItemSlotInfo.Index = InventoryIndex;

		Inventory[InventoryIndex] = ItemSlotInfo;
	}
	else
	{
		Inventory[InventoryIndex].Number--;
	}

	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetOwner()->GetGameInstance());
	ABBHUD* BBHUD = GameIns->HUD;
	AHunter* Hunter = GameIns->Hunter;

	Hunter->PotionBulletUpdate();
	Hunter->UseItemSlotUpdate();

	BBHUD->GetBBStatusInventory()->WidgetUpdate();
	BBHUD->GetBBQuickSlot()->WidgetUpdate();
}



void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

