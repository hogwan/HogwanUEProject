// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/InputWidget.h"
#include "HUD/BBInventorySlot.h"
#include "Components/UniformGridPanel.h"
#include "Components/Image.h"
#include "Global/BBGameInstance.h"
#include "Character/Hunter/BBPlayerController.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void UInputWidget::Enter()
{
}

void UInputWidget::MoveRight()
{
}

void UInputWidget::MoveLeft()
{
}

void UInputWidget::MoveUp()
{
}

void UInputWidget::MoveDown()
{
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

