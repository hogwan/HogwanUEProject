// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Serpmare/BTTaskNode_Serpmare_PatternTerm.h"

EBTNodeResult::Type UBTTaskNode_Serpmare_PatternTerm::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, NodeMemory);

	EMonsterState StateValue = GetCurState<EMonsterState>(_OwnerComp);

	if (StateValue != EMonsterState::EMS_PatternTerm)
	{
		return EBTNodeResult::Type::Failed;
	}

	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);

	if (false == Character->IsValidLowLevel())
	{
		return EBTNodeResult::Aborted;
	}

	if (Character->GetBBAIAnimInstance()->PatternTermMontage == nullptr)
	{
		return EBTNodeResult::Type::Failed;
	}

	Character->GetBBAIAnimInstance()->Montage_Play(Character->GetBBAIAnimInstance()->PatternTermMontage);
	Character->IdleAcc = Character->IdleTime;

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_Serpmare_PatternTerm::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);

	if (!Character) return;

	Character->IdleAcc -= _DeltaSeconds;
	Character->RotateSpeed = 2.f;
	RotateToHunter(_OwnerComp, _DeltaSeconds, Character->RotateSpeed);

	if (Character->IdleAcc < 0.f)
	{
		if (Character->GetAttribute()->Stamina <= 0.f)
		{
			ChangeState(_OwnerComp, EMonsterState::EMS_Lull);
			return;
		}

		if (Character->AttackRange > GetDistanceToHunter(_OwnerComp))
		{
			ChangeState(_OwnerComp, EMonsterState::EMS_Attack);
			return;
		}
		else
		{
			ChangeState(_OwnerComp, EMonsterState::EMS_Shoot);
			return;
		}
	}
}
