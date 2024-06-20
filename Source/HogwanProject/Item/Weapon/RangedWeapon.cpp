// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapon/RangedWeapon.h"

ARangedWeapon::ARangedWeapon()
{
}

void ARangedWeapon::BeginPlay()
{
	Super::BeginPlay();
	EquipHand = EEquipHand::EEH_LeftHand;
}
