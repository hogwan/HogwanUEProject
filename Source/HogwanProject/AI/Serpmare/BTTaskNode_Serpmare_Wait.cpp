// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Serpmare/BTTaskNode_Serpmare_Wait.h"

EBTNodeResult::Type UBTTaskNode_Serpmare_Wait::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, NodeMemory);

	EMonsterState StateValue = GetCurState<EMonsterState>(_OwnerComp);

	if (StateValue != EMonsterState::EMS_Wait)
	{
		return EBTNodeResult::Type::Failed;
	}

	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);

	if (false == Character->IsValidLowLevel())
	{
		return EBTNodeResult::Aborted;
	}

	if (Character->GetBBAIAnimInstance()->IdleMontage == nullptr)
	{
		return EBTNodeResult::Type::Failed;
	}

	Character->GetBBAIAnimInstance()->Montage_Play(Character->GetBBAIAnimInstance()->IdleMontage);

	int MaxIndex = 0;
	float MaxDistance = 0.f;

	for (int i = 1; i < Character->PatrolPoints.Num(); i++)
	{
		FVector PointLocation = Character->PatrolPoints[i];
		FVector HunterLocation = GetHunter()->GetActorLocation();
		PointLocation.Z = 0.f;
		HunterLocation.Z = 0.f;

		float Distance = (PointLocation - HunterLocation).Size();

		if (MaxDistance < Distance)
		{
			MaxIndex = i;
			MaxDistance = Distance;
		}
	}

	Character->SetActorLocation(Character->PatrolPoints[MaxIndex]);


	return EBTNodeResult::InProgress;
}

void UBTTaskNode_Serpmare_Wait::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);

	Character->WaitAcc -= _DeltaSeconds;
	RotateToHunter(_OwnerComp, _DeltaSeconds, Character->RotateSpeed);

	if (Character->WaitAcc < 0.f)
	{
		Character->WaitAcc = Character->WaitTime;
		ChangeState(_OwnerComp, EMonsterState::EMS_Perceive);
		return;
	}
}
