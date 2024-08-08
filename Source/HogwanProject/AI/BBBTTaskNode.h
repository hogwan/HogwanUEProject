// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/Monster/BBAICharacter.h"
#include "Global/BBEnum.h"
#include "Character/Hunter/Hunter.h"
#include "Character/Monster/Monster.h"
#include "AI/BBAIController.h"
#include "ActorComponent/AttributeComponent.h"
#include "BBBTTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class HOGWANPROJECT_API UBBBTTaskNode : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBBBTTaskNode();

	void TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds) override;

	template<typename OwnerType>
	OwnerType* GetController(UBehaviorTreeComponent& _OwnerComp)
	{
		return Cast<OwnerType>(GetController(_OwnerComp));
	}

	AController* GetController(UBehaviorTreeComponent& _OwnerComp);

	template<typename OwnerType>
	OwnerType* GetActor(UBehaviorTreeComponent& _OwnerComp)
	{
		return Cast<OwnerType>(GetActor(_OwnerComp));
	}

	AActor* GetActor(UBehaviorTreeComponent& _OwnerComp);

	template<typename EnumType>
	EnumType GetCurState(UBehaviorTreeComponent& _OwnerComp)
	{
		return static_cast<EnumType>(GetCurState(_OwnerComp));
	}

	uint8 GetCurState(UBehaviorTreeComponent& _OwnerComp);

	class AHunter* GetHunter();

	template<typename EnumType>
	void ChangeState(UBehaviorTreeComponent& _OwnerComp, EnumType _StateChange)
	{
		ChangeState(_OwnerComp, static_cast<uint8>(_StateChange));
	}

	void ChangeState(UBehaviorTreeComponent& _OwnerComp, uint8 _StateChange);

	template<typename ConvertType>
	ConvertType* GetValueAsObject(UBehaviorTreeComponent& _OwnerComp, FName _Name)
	{
		return Cast<ConvertType>(GetValueAsObject(_OwnerComp, _Name));
	}

	FORCEINLINE UObject* GetValueAsObject(UBehaviorTreeComponent& _OwnerComp, FName _Name)
	{
		return _OwnerComp.GetBlackboardComponent()->GetValueAsObject(_Name);
	}

	FORCEINLINE void SetValueAsObject(UBehaviorTreeComponent& _OwnerComp, FName _Name, UObject* _Value)
	{
		_OwnerComp.GetBlackboardComponent()->SetValueAsObject(_Name, _Value);
	}

	bool TargetInRange(UBehaviorTreeComponent& _OwnerComp, float PerceiveRange);

	float BetweenAngleToDegree(UBehaviorTreeComponent& _OwnerComp);

	bool DecideRotationDirection(UBehaviorTreeComponent& _OwnerComp);

	void StatusReset(UBehaviorTreeComponent& _OwnerComp);

	void MoveToHunter(UBehaviorTreeComponent& _OwnerComp, float SuccessRange = 50.f);

	void MoveToPoint(UBehaviorTreeComponent& _OwnerComp, FVector TargetLocation, float SuccessRange = 50.f);

	float GetDistanceToHunter(UBehaviorTreeComponent& _OwnerComp);

	EMonster GetMonsterEnum(UBehaviorTreeComponent& _OwnerComp);

	void RotateToHunter(UBehaviorTreeComponent& _OwnerComp, float DeltaTime, float RotateSpeed);

};
