// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/WomanZombie.h"

void AWomanZombie::GetHit(FVector ImpactPoint)
{
	Super::GetHit(ImpactPoint);

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

	if (AnimInstance && HitMontage)
	{
		AnimInstance->Montage_Play(HitMontage);
	}
}
