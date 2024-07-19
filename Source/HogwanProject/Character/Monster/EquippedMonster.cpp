// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Monster/EquippedMonster.h"
#include "Weapon/MeleeWeapon.h"
#include "Weapon/RangedWeapon.h"
#include "Components/BoxComponent.h"

AEquippedMonster::AEquippedMonster()
{

}

void AEquippedMonster::BeginPlay()
{
	Super::BeginPlay();



}

void AEquippedMonster::DisableRightHandHitBox()
{
	AMeleeWeapon* MeleeWeapon = Cast<AMeleeWeapon>(RightHandWeapon);

	if (MeleeWeapon)
	{
		MeleeWeapon->HitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void AEquippedMonster::DisableLeftHandHitBox()
{
	AMeleeWeapon* MeleeWeapon = Cast<AMeleeWeapon>(LeftHandWeapon);

	if (MeleeWeapon)
	{
		MeleeWeapon->HitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void AEquippedMonster::EnableRightHandHitBox()
{
	AMeleeWeapon* MeleeWeapon = Cast<AMeleeWeapon>(RightHandWeapon);

	if (MeleeWeapon)
	{
		MeleeWeapon->HitBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
}

void AEquippedMonster::EnableLeftHandHitBox()
{
	AMeleeWeapon* MeleeWeapon = Cast<AMeleeWeapon>(LeftHandWeapon);

	if (MeleeWeapon)
	{
		MeleeWeapon->HitBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
}

void AEquippedMonster::Reset()
{
	Super::Reset();


}

void AEquippedMonster::GetHit(const FVector& _ImpactPoint, AActor* _Hitter, EHitType _HitType)
{
	Super::GetHit(_ImpactPoint, _Hitter, _HitType);
}
