// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BBGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class HOGWANPROJECT_API UBBGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	FORCEINLINE class AHunter* GetPlayer() { return Player; }
	FORCEINLINE class UInventory* GetInvectory() { return Inventory; }

private:
	class AHunter* Player;
	class UInventory* Inventory;
};
