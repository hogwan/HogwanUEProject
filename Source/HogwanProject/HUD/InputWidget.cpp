// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/InputWidget.h"
#include "HUD/BBInventorySlot.h"
#include "Components/UniformGridPanel.h"
#include "Components/Image.h"
#include "Global/BBGameInstance.h"
#include "Character/Hunter/BBPlayerController.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Global/BBGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UInputWidget::Enter()
{
	
}

void UInputWidget::MoveRight()
{
	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
	if (GameIns)
	{
		if (GameIns->SoundMap[TEXT("UIMove")])
		{
			UGameplayStatics::PlaySound2D(
				this,
				GameIns->SoundMap["UIMove"]
			);
		}
	}
}

void UInputWidget::MoveLeft()
{
	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
	if (GameIns)
	{
		UGameplayStatics::PlaySound2D(
			this,
			GameIns->SoundMap["UIMove"]
		);
	}
}

void UInputWidget::MoveUp()
{
	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
	if (GameIns)
	{
		UGameplayStatics::PlaySound2D(
			this,
			GameIns->SoundMap["UIMove"]
		);
	}
}

void UInputWidget::MoveDown()
{
	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
	if (GameIns)
	{
		UGameplayStatics::PlaySound2D(
			this,
			GameIns->SoundMap["UIMove"]
		);
	}
}

void UInputWidget::Init()
{
}

void UInputWidget::WidgetUpdate()
{
}

void UInputWidget::CloseWidget()
{
	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
	ABBPlayerController* PlayerController = GameIns->BBPlayerController;

	PlayerController->CloseWidget();
}

