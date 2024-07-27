// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BBHUD.generated.h"

/**
 * 
 */
UCLASS()
class HOGWANPROJECT_API ABBHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UBBOverlay> BBOverlayClass;

	UPROPERTY()
	class UBBOverlay* BBOverlay;


public:
	FORCEINLINE class UBBOverlay* GetBBOverlay() const { return BBOverlay; }

};
