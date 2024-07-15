// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTaskNode_RotateToTarget.h"

EBTNodeResult::Type UBTTaskNode_RotateToTarget::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, NodeMemory);

	EMonsterState StateValue = GetCurState<EMonsterState>(_OwnerComp);

	if (StateValue != EMonsterState::EMS_Rotate)
	{
		return EBTNodeResult::Type::Failed;
	}

	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);

	if (false == Character->IsValidLowLevel())
	{
		return EBTNodeResult::Aborted;
	}

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_RotateToTarget::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);
	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);

	if (Character)
	{
		if (5.f >= BetweenAngleToDegree(_OwnerComp))
		{
			if (Character->PerceiveHunter)
			{
				ChangeState(_OwnerComp, EMonsterState::EMS_Run);
				return;
			}
			else
			{
				ChangeState(_OwnerComp, EMonsterState::EMS_Perceive);
				return;
			}
		}

		RotateToHunter(_OwnerComp, _DeltaSeconds);
	}
}
