// Fill out your copyright notice in the Description page of Project Settings.


#include "BBPlayerController.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "Global/BBGameInstance.h"
#include "Character/Hunter/Hunter.h"
#include "HUD/BBHUD.h"
#include "HUD/BBStatusInventory.h"
#include "HUD/BBQuickSlot.h"
#include "Kismet/GameplayStatics.h"

void ABBPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(EInputMode::Play);

	UBBGameInstance* BBGameInstance = Cast<UBBGameInstance>(GetGameInstance());

	BBGameInstance->Hunter = Cast<AHunter>(GetOwner());
	BBGameInstance->BBPlayerController = this;

}

void ABBPlayerController::SetInputMode(EInputMode _InputMode)
{
	ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
	UEnhancedInputLocalPlayerSubsystem* InputSystem = nullptr;
	if (LocalPlayer)
	{
		InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		if (InputSystem)
		{
			for (const TPair<EInputMode, UInputMappingContext*>& pair : InputMappingContextArrays)
			{
				InputSystem->RemoveMappingContext(pair.Value);
			}
		}
	}

	InputSystem->AddMappingContext(InputMappingContextArrays[_InputMode], 0);
	CurInputMode = _InputMode;
}

void ABBPlayerController::OpenWidget(EInputMode _InputMode)
{
	SetInputMode(_InputMode);

	for (const TPair<EInputMode, UUserWidget*>& pair : AllInputTypeUI)
	{
		if (pair.Key == _InputMode)
		{
			pair.Value->SetVisibility(ESlateVisibility::Visible);
			continue;
		}

		pair.Value->SetVisibility(ESlateVisibility::Hidden);
	}

	AllInputTypeUI[_InputMode]->Init();
	AllInputTypeUI[_InputMode]->WidgetUpdate();

}

void ABBPlayerController::CloseWidget()
{
	for (const TPair<EInputMode, UUserWidget*>& pair : AllInputTypeUI)
	{
		pair.Value->SetVisibility(ESlateVisibility::Hidden);
	}

	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());

	UGameplayStatics::PlaySound2D(
		this,
		GameIns->SoundMap["UIMenuClose"]
	);

	SetInputMode(EInputMode::Play);
}
