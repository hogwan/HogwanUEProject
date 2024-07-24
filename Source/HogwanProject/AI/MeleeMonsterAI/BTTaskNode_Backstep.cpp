// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MeleeMonsterAI/BTTaskNode_Backstep.h"

EBTNodeResult::Type UBTTaskNode_Backstep::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, NodeMemory);

	EMonsterState StateValue = GetCurState<EMonsterState>(_OwnerComp);

	if (StateValue != EMonsterState::EMS_BackStep)
	{
		return EBTNodeResult::Type::Failed;
	}

	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);

	if (false == Character->IsValidLowLevel())
	{
		return EBTNodeResult::Aborted;
	}

	if (Character->GetBBAIAnimInstance()->BackstepMontage == nullptr)
	{
		ChangeState(_OwnerComp, EMonsterState::EMS_Idle);
		return EBTNodeResult::Type::Failed;
	}

	Character->GetBBAIAnimInstance()->Montage_Play(Character->GetBBAIAnimInstance()->BackstepMontage);

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_Backstep::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);
	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);

	RotateToHunter(_OwnerComp, _DeltaSeconds, Character->RotateSpeed);

	EMonster MonsterEnum = GetMonsterEnum(_OwnerComp);
	if (MonsterEnum == EMonster::EM_Mutant)
	{
		Character->AddActorWorldOffset(-Character->GetActorForwardVector() * Character->WalkSpeed * _DeltaSeconds);
	}


	if (Character)
	{
		if (Character->BackstepEnd)
		{
			Character->BackstepEnd = false;
			ChangeState(_OwnerComp, EMonsterState::EMS_Lull);
			return;
		}
	}
}
