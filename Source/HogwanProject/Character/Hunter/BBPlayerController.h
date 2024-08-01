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
	class UInputMappingContext* PlayerInputContext;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputMappingContext* UIStatusInventoryInputContext;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputMappingContext* UIQuickSlotInputContext;

	UFUNCTION(BlueprintCallable)
	void OpenStatusInventory();

	UFUNCTION(BlueprintCallable)
	void OpenQuickSlot();

	UFUNCTION(BlueprintCallable)
	void CloseStatusInventory();

	UFUNCTION(BlueprintCallable)
	void CloseQuickSlot();

};
