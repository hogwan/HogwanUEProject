// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/DeathUI.h"
#include "Character/Hunter/Hunter.h"
#include "Global/BBGameInstance.h"

void UDeathUI::Enter()
{
	Super::Enter();
	UBBGameInstance* GameIns = Cast<UBBGameInstance>(GetGameInstance());
	if (GameIns)
	{
		AHunter* Hunter = GameIns->Hunter;
		if (Hunter)
		{
			Hunter->Revive();
			CloseWidget();
		}
	}
}

void UDeathUI::CloseWidget()
{
	Super::CloseWidget();
}