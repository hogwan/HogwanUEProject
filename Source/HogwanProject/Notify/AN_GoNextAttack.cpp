// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/AN_GoNextAttack.h"
#include "Hunter/Hunter.h"

void UAN_GoNextAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	AHunter* Hunter = Cast<AHunter>(MeshComp->GetOwner());

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
		SectionName += FString::FromInt(NextCount+1);
		FName ConvertedFString = FName(*SectionName);

		Hunter->SetAttackCount(NextCount);
		Hunter->SetGoNextAttack(false);
		AnimInstance->Montage_JumpToSection(ConvertedFString);
	}
}
