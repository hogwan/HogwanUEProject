// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Monster.h"

AMonster::AMonster()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AMonster::BeginPlay()
{
	Super::BeginPlay();
	
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

