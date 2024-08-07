// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/BBHUD.h"
#include "HUD/BBOverlay.h"
#include "HUD/BBStatusInventory.h"
#include "HUD/BBQuickSlot.h"
#include "Character/Hunter/BBPlayerController.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void ABBHUD::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	APlayerController* Controller = World->GetFirstPlayerController();
	if (World)
	{
		if (Controller && BBOverlayClass)
		{
			BBOverlay = CreateWidget<UBBOverlay>(Controller, BBOverlayClass);
			BBOverlay->AddToViewport();
		}
	}

	if (World)
	{
		if (Controller && BBStatusInventoryClass)
		{
			BBStatusInventory = CreateWidget<UBBStatusInventory>(Controller, BBStatusInventoryClass);
			BBStatusInventory->AddToViewport();
			BBStatusInventory->SetVisibility(ESlateVisibility::Hidden);

			ABBPlayerController* BBController = Cast<ABBPlayerController>(Controller);
			BBController->AllInputTypeUI.Add(TPair<EInputMode,UInputWidget*>(EInputMode::StatusInventory, BBStatusInventory));
		}
	}

	if (World)
	{
		if (Controller && BBQuickSlotClass)
		{
			BBQuickSlot = CreateWidget<UBBQuickSlot>(Controller, BBQuickSlotClass);
			BBQuickSlot->AddToViewport();
			BBQuickSlot->SetVisibility(ESlateVisibility::Hidden);

			ABBPlayerController* BBController = Cast<ABBPlayerController>(Controller);
			BBController->AllInputTypeUI.Add(TPair<EInputMode, UInputWidget*>(EInputMode::QuickSlot, BBQuickSlot));
		}
	}
}
