// Fill out your copyright notice in the Description page of Project Settings.


#include "BBPlayerController.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "Global/BBGameInstance.h"
#include "Character/Hunter/Hunter.h"
#include "HUD/BBHUD.h"
#include "HUD/BBStatusInventory.h"

void ABBPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (PlayerInputContext)
			{
				InputSystem->AddMappingContext(PlayerInputContext, 0);
				
			}
		}
	}

	UBBGameInstance* BBGameInstance = Cast<UBBGameInstance>(GetGameInstance());

	BBGameInstance->Hunter = Cast<AHunter>(GetOwner());
}

void ABBPlayerController::OpenStatusInventory()
{
	if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (UIInputContext)
			{
				InputSystem->RemoveMappingContext(PlayerInputContext);
				InputSystem->AddMappingContext(UIInputContext, 0);
			}
		}
	}

	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
	ABBHUD* BBHUD = GameIns->HUD;

	BBHUD->GetBBStatusInventory()->Init();
	BBHUD->GetBBStatusInventory()->SetVisibility(ESlateVisibility::Visible);

}

void ABBPlayerController::OpenQuickSlot()
{
	if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (UIInputContext)
			{
				InputSystem->RemoveMappingContext(PlayerInputContext);
				InputSystem->AddMappingContext(UIInputContext, 0);
			}
		}
	}
}

void ABBPlayerController::CloseStatusInventory()
{
	if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (PlayerInputContext)
			{
				InputSystem->RemoveMappingContext(UIInputContext);
				InputSystem->AddMappingContext(PlayerInputContext, 0);
			}
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
			if (PlayerInputContext)
			{
				InputSystem->RemoveMappingContext(UIInputContext);
				InputSystem->AddMappingContext(PlayerInputContext, 0);
			}
		}
	}
}
