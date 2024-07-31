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


}

void UInventoryComponent::PickUpItem(AItem* _PickUpItem)
{
	int ItemNum = _PickUpItem->GetItemNum();
	EItem Item = _PickUpItem->GetItem();
	EItemType ItemType = _PickUpItem->GetItemType();

	for (TPair<int, TPair<EItem, EItemType>> _ItemSlotInfo : Inventory)
	{
		EItem SlotItem = _ItemSlotInfo.Value.Key;

		if (SlotItem == Item)
		{
			_ItemSlotInfo.Key += ItemNum;
			return;
		}
	}

	TPair<int, TPair<EItem, EItemType>> ItemSlotInfo;
	ItemSlotInfo.Key = ItemNum;
	ItemSlotInfo.Value.Key = Item;
	ItemSlotInfo.Value.Value = ItemType;

	Inventory.Add(ItemSlotInfo);
}

void UInventoryComponent::UseItem(int InventoryIndex)
{
	EItemType ItemType = Inventory[InventoryIndex].Value.Value;

	if (ItemType == EItemType::Weapon || ItemType == EItemType::None) return;

	if (Inventory[InventoryIndex].Key <= 1)
	{
		Inventory.RemoveAt(InventoryIndex);
	}
	else
	{
		Inventory[InventoryIndex].Key--;
	}
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


void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

