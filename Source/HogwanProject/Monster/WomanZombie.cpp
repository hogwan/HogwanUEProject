// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/WomanZombie.h"

void AWomanZombie::GetHit()
{
	Super::GetHit();

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

	if (AnimInstance && HitMontage)
	{
		AnimInstance->Montage_Play(HitMontage);
	}
}
