// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Serpmare/BTTaskNode_Serpmare_Idle.h"

EBTNodeResult::Type UBTTaskNode_Serpmare_Idle::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* NodeMemory)
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

	if (Character->PerceiveHunter)
	{
		if (Character->GetBBAIAnimInstance()->IdleMontage == nullptr)
		{
			return EBTNodeResult::Type::Failed;
		}
	}
	else
	{

	}
	

	



	Character->GetBBAIAnimInstance()->Montage_Play(Character->GetBBAIAnimInstance()->IdleMontage);

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_Serpmare_Idle::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
}
