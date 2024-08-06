// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tool/Item/InteractObject.h"
#include "Global/BBEnum.h"
#include "Item.generated.h"

UCLASS()
class HOGWANPROJECT_API AItem : public AInteractObject
{
	GENERATED_BODY()
	
public:	
	AItem();
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE EItem GetItem() { return Item; }
	FORCEINLINE EItemType GetItemType() { return ItemType; }
	FORCEINLINE int GetItemNum() { return ItemNum; }
	FORCEINLINE EWeapon GetWeapon() { return Weapon; }

	void Interact() override;
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EItem Item = EItem::None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EItemType ItemType = EItemType::None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EWeapon Weapon = EWeapon::None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int ItemNum = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString ItemExplain = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UNiagaraComponent* Effect;

	
};
