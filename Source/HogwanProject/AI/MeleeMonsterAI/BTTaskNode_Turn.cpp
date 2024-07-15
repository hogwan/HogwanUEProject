// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MeleeMonsterAI/BTTaskNode_Turn.h"
#include "Character/Monster/BBAIAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "AI/BBAIController.h"

EBTNodeResult::Type UBTTaskNode_Turn::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, NodeMemory);

	EMonsterState StateValue = GetCurState<EMonsterState>(_OwnerComp);

	if (StateValue != EMonsterState::EMS_Turn)
	{
		return EBTNodeResult::Type::Failed;
	}

	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);

	if (false == Character->IsValidLowLevel())
	{
		return EBTNodeResult::Aborted;
	}

	if (Character->GetBBAIAnimInstance()->TurnMontage == nullptr)
	{
		Character->TurnEnd = true;
		return EBTNodeResult::InProgress;
	}

	Character->GetBBAIAnimInstance()->Montage_Play(Character->GetBBAIAnimInstance()->TurnMontage);

	if (DecideRotationDirection(_OwnerComp))
	{
		Character->GetBBAIAnimInstance()->Montage_JumpToSection(TEXT("TurnRight"));
	}
	else
	{
		Character->GetBBAIAnimInstance()->Montage_JumpToSection(TEXT("TurnLeft"));
	}

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_Turn::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);
	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);

	if (Character)
	{
		if (Character->TurnEnd)
		{
			Character->TurnEnd = false;

			ChangeState(_OwnerComp, EMonsterState::EMS_Rotate);
			return;
		}
	}
}
