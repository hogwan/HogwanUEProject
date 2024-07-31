// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Global/BBEnum.h"
#include "InventoryComponent.generated.h"

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
	TArray<TPair<int,TPair<EItem, EItemType>>> Inventory;

	UFUNCTION(BlueprintCallable)
	void PickUpItem(class AItem* _PickUpItem);

	UFUNCTION(BlueprintCallable)
	void UseItem(int InventoryIndex);

	UFUNCTION(BlueprintCallable)
	void ItemAction(EItem _Item);
};
