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

	EquipRightHandWeapon();
	EquipLeftHandWeapon();

	AMeleeWeapon* LeftMeleeWeapon = Cast<AMeleeWeapon>(LeftHandWeapon);

	if (LeftMeleeWeapon)
	{
		LeftMeleeWeapon->HitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	AMeleeWeapon* RightMeleeWeapon = Cast<AMeleeWeapon>(RightHandWeapon);

	if (RightMeleeWeapon)
	{
		RightMeleeWeapon->HitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

}

void AEquippedMonster::DisableRightHandHitBox()
{
	AMeleeWeapon* MeleeWeapon = Cast<AMeleeWeapon>(RightHandWeapon);

	if (MeleeWeapon)
	{
		MeleeWeapon->HitBoxOff();
	}
}

void AEquippedMonster::DisableLeftHandHitBox()
{
	AMeleeWeapon* MeleeWeapon = Cast<AMeleeWeapon>(LeftHandWeapon);

	if (MeleeWeapon)
	{
		MeleeWeapon->HitBoxOff();
	}
}

void AEquippedMonster::EnableRightHandHitBox()
{
	if (RightHandWeapon->WeaponType != EWeaponType::EWT_MeleeWeapon) return;

	AMeleeWeapon* MeleeWeapon = Cast<AMeleeWeapon>(RightHandWeapon);

	if (MeleeWeapon)
	{
		MeleeWeapon->HitBoxOn();
	}
}

void AEquippedMonster::EnableLeftHandHitBox()
{
	if (LeftHandWeapon->WeaponType != EWeaponType::EWT_MeleeWeapon) return;

	AMeleeWeapon* MeleeWeapon = Cast<AMeleeWeapon>(LeftHandWeapon);

	if (MeleeWeapon)
	{
		MeleeWeapon->HitBoxOn();
	}
}

void AEquippedMonster::Reset()
{
	Super::Reset();


}

void AEquippedMonster::GetHit(const FVector& _ImpactPoint, AActor* _Hitter, EHitType _HitType)
{
	Super::GetHit(_ImpactPoint, _Hitter, _HitType);
	
	DisableRightHandHitBox();
	DisableLeftHandHitBox();
}

void AEquippedMonster::EquipRightHandWeapon()
{
	FTransform SpawnTrans;
	SpawnTrans.SetLocation(GetActorLocation() + FVector::DownVector * 10000.f);

	AWeapon* SpawnWeapon = GetWorld()->SpawnActor<AWeapon>(MonsterRightHandWeapon, SpawnTrans);
	FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);

	switch (SpawnWeapon->WeaponType)
	{
	case EWeaponType::EWT_MeleeWeapon:
		RightHandWeapon = Cast<AMeleeWeapon>(SpawnWeapon);
		break;
	case EWeaponType::EWT_RangedWeapon:
		RightHandWeapon = Cast<ARangedWeapon>(SpawnWeapon);
		break;
	default:
		break;
	}

	RightHandWeapon->AttachToComponent(GetMesh(), AttachRules, TEXT("RightHandSocket"));
	RightHandWeapon->SetOwner(this);
}

void AEquippedMonster::EquipLeftHandWeapon()
{
	FTransform SpawnTrans;
	SpawnTrans.SetLocation(GetActorLocation() + FVector::DownVector * 10000.f);

	AWeapon* SpawnWeapon = GetWorld()->SpawnActor<AWeapon>(MonsterLeftHandWeapon, SpawnTrans);
	FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);

	switch (SpawnWeapon->WeaponType)
	{
	case EWeaponType::EWT_MeleeWeapon:
		LeftHandWeapon = Cast<AMeleeWeapon>(SpawnWeapon);
		break;
	case EWeaponType::EWT_RangedWeapon:
		LeftHandWeapon = Cast<ARangedWeapon>(SpawnWeapon);
		break;
	default:
		break;
	}

	LeftHandWeapon->AttachToComponent(GetMesh(), AttachRules, TEXT("LeftHandSocket"));
	LeftHandWeapon->SetOwner(this);
}
