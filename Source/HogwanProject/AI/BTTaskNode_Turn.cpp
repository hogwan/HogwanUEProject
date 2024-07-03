// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTaskNode_Turn.h"
#include "AI/BBAIAnimInstance.h"
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
			if (Character->PerceiveHunter)
			{
				Character->GetBBAIAnimInstance()->Montage_Play(Character->GetBBAIAnimInstance()->RunMontage);
				ChangeState(_OwnerComp, EMonsterState::EMS_Run);
				return;
			}
			else
			{
				ChangeState(_OwnerComp, EMonsterState::EMS_Perceive);
				return;	
			}

		}
	}
}
