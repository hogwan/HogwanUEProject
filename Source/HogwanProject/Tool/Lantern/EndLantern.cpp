// Fill out your copyright notice in the Description page of Project Settings.


#include "Tool/Lantern/EndLantern.h"
#include "Kismet/GameplayStatics.h"

void AEndLantern::Interact()
{
	Super::Interact();

	UGameplayStatics::OpenLevel(this, FName(TEXT("EndLevel")), true);
}
