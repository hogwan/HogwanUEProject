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
	AMeleeWeapon* MeleeWeapon = Cast<AMeleeWeapon>(RightHandWeapon);

	if (MeleeWeapon)
	{
		MeleeWeapon->HitBoxOn();
	}
}

void AEquippedMonster::EnableLeftHandHitBox()
{
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
}

void AEquippedMonster::EquipRightHandWeapon()
{
	FTransform SpawnTrans;
	SpawnTrans.SetLocation(GetActorLocation() + FVector::DownVector * 10000.f);

	AWeapon* SpawnWeapon = GetWorld()->SpawnActor<AWeapon>(MutantRightHandWeapon, SpawnTrans);
	FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);

	RightHandWeapon = Cast<AMeleeWeapon>(SpawnWeapon);
	RightHandWeapon->AttachToComponent(GetMesh(), AttachRules, TEXT("RightHandSocket"));
	RightHandWeapon->SetOwner(this);
}

void AEquippedMonster::EquipLeftHandWeapon()
{
	FTransform SpawnTrans;
	SpawnTrans.SetLocation(GetActorLocation() + FVector::DownVector * 10000.f);

	AWeapon* SpawnWeapon = GetWorld()->SpawnActor<AWeapon>(MutantLeftHandWeapon, SpawnTrans);
	FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);

	LeftHandWeapon = Cast<AMeleeWeapon>(SpawnWeapon);
	LeftHandWeapon->AttachToComponent(GetMesh(), AttachRules, TEXT("LeftHandSocket"));
	LeftHandWeapon->SetOwner(this);
}
