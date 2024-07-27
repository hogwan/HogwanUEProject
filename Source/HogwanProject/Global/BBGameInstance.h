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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AActor* LockOnTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AHunter* Hunter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ABBHUD* HUD;

};
