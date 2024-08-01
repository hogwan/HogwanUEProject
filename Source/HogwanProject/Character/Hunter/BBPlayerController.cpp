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
}

void ABBPlayerController::CloseStatusInventory()
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

	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
	ABBHUD* BBHUD = GameIns->HUD;

	BBHUD->GetBBStatusInventory()->Init();
	BBHUD->GetBBStatusInventory()->SetVisibility(ESlateVisibility::Hidden);
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
