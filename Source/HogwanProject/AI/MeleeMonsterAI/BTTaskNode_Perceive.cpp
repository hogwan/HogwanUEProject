// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MeleeMonsterAI/BTTaskNode_Perceive.h"
#include "Character/Monster/BBAIAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"

EBTNodeResult::Type UBTTaskNode_Perceive::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, NodeMemory);

	EMonsterState StateValue = GetCurState<EMonsterState>(_OwnerComp);

	if (StateValue != EMonsterState::EMS_Perceive)
	{
		return EBTNodeResult::Type::Failed;
	}

	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);

	if (false == Character->IsValidLowLevel())
	{
		return EBTNodeResult::Aborted;
	}

	ABBAIController* Controller = GetController<ABBAIController>(_OwnerComp);
	Controller->StopMovement();


	if (Character->GetBBAIAnimInstance()->PerceiveMontage != nullptr)
	{
		Character->GetBBAIAnimInstance()->Montage_Play(Character->GetBBAIAnimInstance()->PerceiveMontage);
	}
	else
	{
		ChangeState(_OwnerComp, EMonsterState::EMS_Run);
		return EBTNodeResult::Failed;
	}


	return EBTNodeResult::InProgress;
}

void UBTTaskNode_Perceive::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);
	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);
	if (Character)
	{
		if (Character->PerceiveEnd)
		{
			Character->PerceiveEnd = false;
			ChangeState(_OwnerComp, EMonsterState::EMS_Run);
			return;
		}
	}
}
