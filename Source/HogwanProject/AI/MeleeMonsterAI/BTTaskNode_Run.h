// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/BBBTTaskNode.h"
#include "BTTaskNode_Run.generated.h"

/**
 * 
 */
UCLASS()
class HOGWANPROJECT_API UBTTaskNode_Run : public UBBBTTaskNode
{
	GENERATED_BODY()
	
public:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* NodeMemory) override;

	void TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds) override;
};
