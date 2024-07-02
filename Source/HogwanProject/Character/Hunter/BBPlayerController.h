// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BBPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class HOGWANPROJECT_API ABBPlayerController : public APlayerController
{
	GENERATED_BODY()

	void BeginPlay() override;
	

public:
	UPROPERTY(EditAnywhere, Category = Input)
	class UInputMappingContext* InputContext;
};
