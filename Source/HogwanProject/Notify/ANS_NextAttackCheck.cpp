// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/ANS_NextAttackCheck.h"
#include "Character/Hunter/Hunter.h"

void UANS_NextAttackCheck::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	Hunter = Cast<AHunter>(MeshComp->GetOwner());
}

void UANS_NextAttackCheck::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if (Hunter)
	{
		if (Hunter->GetGoNextAttack() == false) return;

		UAnimInstance* AnimInstance = MeshComp->GetAnimInstance();

		int AttackCount = Hunter->GetAttackCount();

		int NextCount = 0;

		switch (AttackCount)
		{
		case 0:
			NextCount = 1;
			break;
		case 1:
			NextCount = 0;
			break;
		default:
			break;
		}

		FString SectionName = "Attack";
		SectionName += FString::FromInt(NextCount + 1);
		FName ConvertedFString = FName(*SectionName);

		Hunter->SetAttackCount(NextCount);
		Hunter->SetGoNextAttack(false);
		AnimInstance->Montage_JumpToSection(ConvertedFString);
	}
}
