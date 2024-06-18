// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Hunter/Hunter.h"
#include "BBGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class HOGWANPROJECT_API UBBGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	FORCEINLINE AHunter* GetPlayer() { return Player; }

private:
	AHunter* Player;
};
