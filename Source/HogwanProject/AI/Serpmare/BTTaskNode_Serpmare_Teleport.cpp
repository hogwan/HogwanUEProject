// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Serpmare/BTTaskNode_Serpmare_Teleport.h"

EBTNodeResult::Type UBTTaskNode_Serpmare_Teleport::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, NodeMemory);

	EMonsterState StateValue = GetCurState<EMonsterState>(_OwnerComp);

	if (StateValue != EMonsterState::EMS_Lull)
	{
		return EBTNodeResult::Type::Failed;
	}

	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);

	if (false == Character->IsValidLowLevel())
	{
		return EBTNodeResult::Aborted;
	}

	if (Character->GetBBAIAnimInstance()->LullMontage == nullptr)
	{
		return EBTNodeResult::Type::Failed;
	}

	Character->GetBBAIAnimInstance()->Montage_Play(Character->GetBBAIAnimInstance()->LullMontage);

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_Serpmare_Teleport::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);

	if (Character->LullEnd)
	{
		Character->LullEnd = false;

		ChangeState(_OwnerComp, EMonsterState::EMS_Wait);
		return;
	}
	
}
