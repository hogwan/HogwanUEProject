// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTaskNode_Idle.h"

EBTNodeResult::Type UBTTaskNode_Idle::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, NodeMemory);


	return EBTNodeResult::Type();
}

void UBTTaskNode_Idle::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
}
