// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/BBBTTaskNode.h"
#include "BTTaskNode_Idle.generated.h"

/**
 * 
 */
UCLASS()
class HOGWANPROJECT_API UBTTaskNode_Idle : public UBBBTTaskNode
{
	GENERATED_BODY()

public:
	// 이 노드가 처음 실행될때 들어옵니다.
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* NodeMemory) override;

	void TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds) override;
};
