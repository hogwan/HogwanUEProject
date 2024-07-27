// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/BBHUD.h"
#include "HUD/BBOverlay.h"

void ABBHUD::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* Controller = World->GetFirstPlayerController();
		if (Controller && BBOverlayClass)
		{
			BBOverlay = CreateWidget<UBBOverlay>(Controller, BBOverlayClass);
			BBOverlay->AddToViewport();
		}
	}


}
