// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/OldHunter/BTTaskNode_OldHunter_Backstep.h"

EBTNodeResult::Type UBTTaskNode_OldHunter_Backstep::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* NodeMemory)
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
		return EBTNodeResult::Type::Failed;
	}
	Character->GetBBAIAnimInstance()->Montage_Play(Character->GetBBAIAnimInstance()->BackstepMontage);

	ABBAIController* Controller = GetController<ABBAIController>(_OwnerComp);
	Controller->StopMovement();

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_OldHunter_Backstep::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);
	RotateToHunter(_OwnerComp, _DeltaSeconds, 5.f);

	if (Character->BackstepEnd)
	{
		Character->BackstepEnd = false;

		ChangeState(_OwnerComp, EMonsterState::EMS_BackWalk);
		return;
	}
}
