// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Monster.h"
#include "HUD/HealthBarComponent.h"
#include "ActorComponent/AttributeComponent.h"

AMonster::AMonster()
{
	PrimaryActorTick.bCanEverTick = true;

	LockOnTargetWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("LockOnTarget"));
	LockOnTargetWidget->SetupAttachment(GetRootComponent());

}

void AMonster::BeginPlay()
{
	Super::BeginPlay();

	if (LockOnTargetWidget)
	{
		LockOnTargetWidget->SetVisibility(false);
	}

}

void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
