// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Serpmare/BTTaskNode_Serpmare_GetOut.h"

EBTNodeResult::Type UBTTaskNode_Serpmare_GetOut::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, NodeMemory);

	EMonsterState StateValue = GetCurState<EMonsterState>(_OwnerComp);

	if (StateValue != EMonsterState::EMS_Perceive)
	{
		return EBTNodeResult::Type::Failed;
	}

	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);

	if (false == Character->IsValidLowLevel())
	{
		return EBTNodeResult::Aborted;
	}

	if (Character->GetBBAIAnimInstance()->PerceiveMontage == nullptr)
	{
		return EBTNodeResult::Type::Failed;
	}

	Character->GetBBAIAnimInstance()->Montage_Play(Character->GetBBAIAnimInstance()->PerceiveMontage);


	return EBTNodeResult::InProgress;
}

void UBTTaskNode_Serpmare_GetOut::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);

	if (!Character) return;

	if (Character->PerceiveEnd)
	{
		Character->PerceiveEnd = false;
		
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

		return;
	}
}
