// Fill out your copyright notice in the Description page of Project Settings.


#include "BBPlayerController.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "Global/BBGameInstance.h"
#include "Character/Hunter/Hunter.h"

void ABBPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputContext)
			{
				InputSystem->AddMappingContext(InputContext, 0);
			}
		}
	}

	UBBGameInstance* BBGameInstance = Cast<UBBGameInstance>(GetGameInstance());

	BBGameInstance->Hunter = Cast<AHunter>(GetOwner());
}
