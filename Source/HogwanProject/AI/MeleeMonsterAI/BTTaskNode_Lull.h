// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/BBBTTaskNode.h"
#include "BTTaskNode_Lull.generated.h"

/**
 * 
 */
UCLASS()
class HOGWANPROJECT_API UBTTaskNode_Lull : public UBBBTTaskNode
{
	GENERATED_BODY()
public:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* NodeMemory) override;

	void TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds) override;

	void ExecuteParasiteLull(UBehaviorTreeComponent& _OwnerComp);
	void UpdateParasiteLull(UBehaviorTreeComponent& _OwnerComp, float _DeltaSeconds);
	void ExecuteWolfLull(UBehaviorTreeComponent& _OwnerComp);
};
