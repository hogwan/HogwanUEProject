// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTaskNode_Dead.h"

EBTNodeResult::Type UBTTaskNode_Dead::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, NodeMemory);

	EMonsterState StateValue = GetCurState<EMonsterState>(_OwnerComp);

	if (StateValue != EMonsterState::EMS_Dead)
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

void UBTTaskNode_Dead::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	ABBAICharacter* Monster = GetActor<ABBAICharacter>(_OwnerComp);
	if (!Monster) return;

	Monster->DestroyTime -= _DeltaSeconds;

	if (Monster->DestroyTime < 0.f)
	{
		Monster->Destroy();
		return;
	}
}
