// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/OldHunter/BTTaskNode_OldHunter_Shoot.h"

EBTNodeResult::Type UBTTaskNode_OldHunter_Shoot::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, NodeMemory);

	EMonsterState StateValue = GetCurState<EMonsterState>(_OwnerComp);

	if (StateValue != EMonsterState::EMS_Shoot)
	{
		return EBTNodeResult::Type::Failed;
	}

	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);

	if (false == Character->IsValidLowLevel())
	{
		return EBTNodeResult::Aborted;
	}

	if (Character->GetBBAIAnimInstance()->ShootMontage == nullptr)
	{
		return EBTNodeResult::Type::Failed;
	}
	Character->GetBBAIAnimInstance()->Montage_Play(Character->GetBBAIAnimInstance()->ShootMontage);

	ABBAIController* Controller = GetController<ABBAIController>(_OwnerComp);
	Controller->StopMovement();

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_OldHunter_Shoot::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);

	if (Character->AttackEnd)
	{
		Character->AttackEnd = false;

		ChangeState(_OwnerComp, EMonsterState::EMS_Lull);
		return;
	}
}
