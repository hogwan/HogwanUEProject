// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTaskNode_Idle.h"
#include "GameFramework/CharacterMovementComponent.h"

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

	ABBAIController* MonsterController = GetController<ABBAIController>(_OwnerComp);

	if (Character->GetBBAIAnimInstance()->IdleMontage == nullptr)
	{
		return EBTNodeResult::Type::Failed;
	}

	Character->GetBBAIAnimInstance()->Montage_Play(Character->GetBBAIAnimInstance()->IdleMontage);

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_Idle::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);
	
	ABBAICharacter* Monster = GetActor<ABBAICharacter>(_OwnerComp);
	if (!Monster) return;

	if (Monster->CurStamina <= 0.f)
	{
		ChangeState(_OwnerComp, EMonsterState::EMS_BackStep);
		return;
	}



	Monster->IdleAcc -= _DeltaSeconds;

	if (Monster->IdleAcc < 0.f)
	{
		ChangeState(_OwnerComp,EMonsterState::EMS_Patrol);
		return;
	}

	if (Monster->PerceiveHunter || PerceiveInRange(_OwnerComp, Monster->PerceiveRange))
	{
		if (BetweenAngleToDegree(_OwnerComp) > 90.f)
		{
			ChangeState(_OwnerComp, EMonsterState::EMS_Turn);
			return;
		}

		if (Monster->PerceiveHunter)
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
}
