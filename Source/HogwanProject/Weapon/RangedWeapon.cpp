// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/RangedWeapon.h"

ARangedWeapon::ARangedWeapon()
{
	BulletSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("BulletSpawnPoint"));
	BulletSpawnPoint->SetupAttachment(GetRootComponent());
}

void ARangedWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARangedWeapon::BeginPlay()
{
	Super::BeginPlay();
}
