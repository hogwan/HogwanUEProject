// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/BBBTTaskNode.h"
#include "BTTaskNode_Attack.generated.h"

/**
 * 
 */
UCLASS()
class HOGWANPROJECT_API UBTTaskNode_Attack : public UBBBTTaskNode
{
	GENERATED_BODY()
public:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* NodeMemory) override;

	void TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds) override;

	void ExecuteZombieAttack(UBehaviorTreeComponent& _OwnerComp);
	void ExecuteParasiteAttack(UBehaviorTreeComponent& _OwnerComp);
	void ExecuteWolfAttack(UBehaviorTreeComponent& _OwnerComp);
	void ExecuteMutantAttack(UBehaviorTreeComponent& _OwnerComp);
};
