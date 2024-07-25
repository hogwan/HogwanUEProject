// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/OldHunter/BTTaskNode_OldHunter_DashAttack.h"

EBTNodeResult::Type UBTTaskNode_OldHunter_DashAttack::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, NodeMemory);

	EMonsterState StateValue = GetCurState<EMonsterState>(_OwnerComp);

	if (StateValue != EMonsterState::EMS_DashAttack)
	{
		return EBTNodeResult::Type::Failed;
	}

	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);

	if (false == Character->IsValidLowLevel())
	{
		return EBTNodeResult::Aborted;
	}

	if (Character->GetBBAIAnimInstance()->DashAttackMontage == nullptr)
	{
		return EBTNodeResult::Type::Failed;
	}
	Character->GetBBAIAnimInstance()->Montage_Play(Character->GetBBAIAnimInstance()->DashAttackMontage);

	ABBAIController* Controller = GetController<ABBAIController>(_OwnerComp);
	Controller->StopMovement();

	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNode_OldHunter_DashAttack::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);

	if (Character->AttackEnd)
	{
		Character->AttackEnd = false;

		float Distance = GetDistanceToHunter(_OwnerComp);

		if (Distance < Character->CombatDistance)
		{
			ChangeState(_OwnerComp, EMonsterState::EMS_BackStep);
			return;
		}
		else
		{
			ChangeState(_OwnerComp, EMonsterState::EMS_Lull);
			return;
		}
	}
}
