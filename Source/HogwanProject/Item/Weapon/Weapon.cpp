// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapon/Weapon.h"

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	ItemType = EItemType::EIT_Weapon;
}
