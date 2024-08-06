// Fill out your copyright notice in the Description page of Project Settings.


#include "BBPlayerController.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "Global/BBGameInstance.h"
#include "Character/Hunter/Hunter.h"
#include "HUD/BBHUD.h"
#include "HUD/BBStatusInventory.h"
#include "HUD/BBQuickSlot.h"

void ABBPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			InputSystem->AddMappingContext(PlayerInputContext, 0);
		}
	}

	UBBGameInstance* BBGameInstance = Cast<UBBGameInstance>(GetGameInstance());

	BBGameInstance->Hunter = Cast<AHunter>(GetOwner());
	BBGameInstance->BBPlayerController = this;
}

void ABBPlayerController::OpenStatusInventory()
{
	if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			InputSystem->RemoveMappingContext(PlayerInputContext);
			InputSystem->RemoveMappingContext(UIQuickSlotInputContext);
			InputSystem->AddMappingContext(UIStatusInventoryInputContext, 0);
		}
	}

	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
	ABBHUD* BBHUD = GameIns->HUD;

	BBHUD->GetBBQuickSlot()->SetVisibility(ESlateVisibility::Hidden);

	BBHUD->GetBBStatusInventory()->Init();
	BBHUD->GetBBStatusInventory()->SetVisibility(ESlateVisibility::Visible);

	BBHUD->GetBBStatusInventory()->UpdateInventory();
	BBHUD->GetBBQuickSlot()->UpdateQuickSlot();

}

void ABBPlayerController::OpenQuickSlot()
{
	if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			InputSystem->RemoveMappingContext(PlayerInputContext);
			InputSystem->RemoveMappingContext(UIStatusInventoryInputContext);
			InputSystem->AddMappingContext(UIQuickSlotInputContext, 0);
		}
	}

	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
	ABBHUD* BBHUD = GameIns->HUD;

	BBHUD->GetBBStatusInventory()->SetVisibility(ESlateVisibility::Hidden);

	BBHUD->GetBBQuickSlot()->Init();
	BBHUD->GetBBQuickSlot()->SetVisibility(ESlateVisibility::Visible);

	BBHUD->GetBBStatusInventory()->UpdateInventory();
	BBHUD->GetBBQuickSlot()->UpdateQuickSlot();
}

void ABBPlayerController::CloseStatusInventory()
{
	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
	ABBHUD* BBHUD = GameIns->HUD;

	if (BBHUD->QuickSlotData.IsQuickSlotSetting)
	{
		if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
		{
			if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				InputSystem->RemoveMappingContext(UIStatusInventoryInputContext);
				InputSystem->RemoveMappingContext(PlayerInputContext);
				InputSystem->AddMappingContext(UIQuickSlotInputContext, 0);
			}
		}
		BBHUD->GetBBStatusInventory()->SetVisibility(ESlateVisibility::Hidden);
		BBHUD->GetBBQuickSlot()->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
		{
			if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				InputSystem->RemoveMappingContext(UIStatusInventoryInputContext);
				InputSystem->RemoveMappingContext(UIQuickSlotInputContext);
				InputSystem->AddMappingContext(PlayerInputContext, 0);
			}
		}

		BBHUD->GetBBStatusInventory()->Init();
		BBHUD->GetBBStatusInventory()->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ABBPlayerController::CloseQuickSlot()
{
	if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			InputSystem->RemoveMappingContext(UIStatusInventoryInputContext);
			InputSystem->AddMappingContext(PlayerInputContext, 0);
		}
	}

	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
	ABBHUD* BBHUD = GameIns->HUD;

	BBHUD->GetBBQuickSlot()->Init();
	BBHUD->GetBBQuickSlot()->SetVisibility(ESlateVisibility::Hidden);
}
