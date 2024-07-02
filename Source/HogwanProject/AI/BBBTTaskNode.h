// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BlackboardComponent.h"
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

	template<typename EnumType>
	AActor* GetTarget(UBehaviorTreeComponent& _OwnerComp, float _Range, EnumType _Target, bool _ZIgnore = true)
	{
		return GetTarget(_OwnerComp, _Range, static_cast<uint8>(_Target), _ZIgnore);
	}

	AActor* GetTarget(UBehaviorTreeComponent& _OwnerComp, float _Range, uint8 Target, bool _ZIgnore = true);

	template<typename EnumType>
	AActor* CheckTarget(UBehaviorTreeComponent& _OwnerComp, float _Range, EnumType Target, bool _ZIgnore = true)
	{
		return CheckTarget(_OwnerComp, _Range, static_cast<uint8>(Target), _ZIgnore);
	}

	AActor* CheckTarget(UBehaviorTreeComponent& _OwnerComp, float _Range, uint8 Target, bool _ZIgnore = true);

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
};
