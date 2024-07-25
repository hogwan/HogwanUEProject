// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/OldHunter/BTTaskNode_OldHunter_Idle.h"

EBTNodeResult::Type UBTTaskNode_OldHunter_Idle::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* NodeMemory)
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

void UBTTaskNode_OldHunter_Idle::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);

	if (Character->PerceiveHunter)
	{
		ChangeState(_OwnerComp, EMonsterState::EMS_Run);
		return;
	}
}
