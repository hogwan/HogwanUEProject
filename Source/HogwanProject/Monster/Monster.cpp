// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Monster.h"
#include "HUD/HealthBarComponent.h"

AMonster::AMonster()
{
	PrimaryActorTick.bCanEverTick = true;


	HealthBarWidget = CreateDefaultSubobject<UHealthBarComponent>(TEXT("HealthBar"));
	HealthBarWidget->SetupAttachment(GetRootComponent());
}

void AMonster::BeginPlay()
{
	Super::BeginPlay();
	
	if (HealthBarWidget)
	{
		HealthBarWidget->SetHealthPercent(.1f);
	}

}

void AMonster::GetHit()
{
}

void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

