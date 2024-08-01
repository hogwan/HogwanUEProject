// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponent/InventoryComponent.h"
#include "Tool/Item/Item.h"

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
		Inventory.Add(ItemSlotInfo);
	}
}

void UInventoryComponent::PickUpItem(AItem* _PickUpItem)
{
	int ItemNum = _PickUpItem->GetItemNum();
	EItem Item = _PickUpItem->GetItem();
	EItemType ItemType = _PickUpItem->GetItemType();

	for (FInvenSlotData _ItemSlotInfo : Inventory)
	{
		EItem SlotItem = _ItemSlotInfo.Item;
		bool IsEmpty = _ItemSlotInfo.IsEmpty;

		if (SlotItem == Item)
		{
			_ItemSlotInfo.Number += ItemNum;
			return;
		}

		if (IsEmpty)
		{
			FInvenSlotData TempItemSlotInfo;
			TempItemSlotInfo.IsEmpty = false;
			TempItemSlotInfo.Number = ItemNum;
			TempItemSlotInfo.Item = Item;
			TempItemSlotInfo.ItemType = ItemType;

			_ItemSlotInfo = TempItemSlotInfo;
		}
	}
}

void UInventoryComponent::UseItem(int InventoryIndex)
{
	EItemType ItemType = Inventory[InventoryIndex].ItemType;

	if (ItemType == EItemType::Weapon || ItemType == EItemType::None) return;

	if (Inventory[InventoryIndex].Number <= 1)
	{
		Inventory[InventoryIndex] = FInvenSlotData();
	}
	else
	{
		Inventory[InventoryIndex].Number--;
	}

	SortInventory();
}

void UInventoryComponent::ItemAction(EItem _Item)
{
	switch (_Item)
	{
	case EItem::FireBottle:
		break;
	case EItem::Potion:
		break;
	}

}

void UInventoryComponent::SortInventory()
{
	int Index = 0;
	TArray<FInvenSlotData> TempArray;

	for (int i = 0; i < 12; i++)
	{
		FInvenSlotData ItemSlotInfo;
		TempArray.Add(ItemSlotInfo);
	}

	for (FInvenSlotData Data : Inventory)
	{
		if (!Data.IsEmpty)
		{
			TempArray[Index] = Data;
			Index++;
		}
	}
	
	Inventory = TempArray;
}


void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

