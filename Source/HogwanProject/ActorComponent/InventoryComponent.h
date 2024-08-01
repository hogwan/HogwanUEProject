// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Global/BBEnum.h"
#include "InventoryComponent.generated.h"

USTRUCT(BlueprintType)
struct FInvenSlotData
{
	GENERATED_BODY()

	bool IsEmpty = true;

	int Number = 0;
	EItem Item = EItem::None;
	EItemType ItemType = EItemType::None;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HOGWANPROJECT_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FInvenSlotData> Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FInvenSlotData> QuickSlot;

	UFUNCTION(BlueprintCallable)
	void PickUpItem(class AItem* _PickUpItem);

	UFUNCTION(BlueprintCallable)
	void UseItem(int InventoryIndex);

	UFUNCTION(BlueprintCallable)
	void ItemAction(EItem _Item);

	void SortInventory();

};
