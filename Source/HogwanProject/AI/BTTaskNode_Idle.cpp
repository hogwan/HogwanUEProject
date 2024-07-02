// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTaskNode_Idle.h"

EBTNodeResult::Type UBTTaskNode_Idle::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, NodeMemory);

	EMonsterState StateValue = GetCurState<EMonsterState>(_OwnerComp);

	if (StateValue != EMonsterState::EMS_Idle)
	{
		return EBTNodeResult::Type::Failed;
	}

	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);

	if (false == Character->IsValidLowLevel())
	{
		return EBTNodeResult::Aborted;
	}

	Character->ChangeAnimation(EMonsterAnimation::EMA_Idle);

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_Idle::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);
	
	ABBAICharacter* Monster = GetActor<ABBAICharacter>(_OwnerComp);
	if (!Monster) return;

	Monster->IdleAcc -= _DeltaSeconds;

	if (Monster->IdleAcc < 0.f)
	{
		TimeReset(_OwnerComp);
		ChangeState(_OwnerComp,EMonsterState::EMS_Patrol);
		return;
	}

	if (PerceiveInRange(_OwnerComp, 300.f))
	{
		if (BetweenAngleToDegree(_OwnerComp) > 60.f)
		{
			TimeReset(_OwnerComp);
			ChangeState(_OwnerComp, EMonsterState::EMS_Turn);
			return;
		}

		TimeReset(_OwnerComp);
		ChangeState(_OwnerComp, EMonsterState::EMS_Perceive);
		return;
	}

}
