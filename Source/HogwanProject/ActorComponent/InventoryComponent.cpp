// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponent/InventoryComponent.h"
#include "Tool/Item/Item.h"
#include "Global/BBGameInstance.h"
#include "HUD/BBStatusInventory.h"
#include "HUD/BBHUD.h"
#include "Character/Hunter/Hunter.h"

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

}

void UInventoryComponent::PickUpItem(AItem* _PickUpItem)
{
	int ItemNum = _PickUpItem->GetItemNum();
	EItem Item = _PickUpItem->GetItem();
	EItemType ItemType = _PickUpItem->GetItemType();
	EWeapon Weapon = _PickUpItem->GetWeapon();

	for (FInvenSlotData& _ItemSlotInfo : Inventory)
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
			TempItemSlotInfo.Weapon = Weapon;

			_ItemSlotInfo = TempItemSlotInfo;
			break;
		}
	}

	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetOwner()->GetGameInstance());
	ABBHUD* BBHUD = GameIns->HUD;
	BBHUD->GetBBStatusInventory()->UpdateInventory();
}

void UInventoryComponent::UseItem(int InventoryIndex)
{
	EItemType ItemType = Inventory[InventoryIndex].ItemType;

	if (ItemType != EItemType::UseItem) return;

	if (Inventory[InventoryIndex].Number <= 1)
	{
		Inventory[InventoryIndex] = FInvenSlotData();
	}
	else
	{
		Inventory[InventoryIndex].Number--;
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

