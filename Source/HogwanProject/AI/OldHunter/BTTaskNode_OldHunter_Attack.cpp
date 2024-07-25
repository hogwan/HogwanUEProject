// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/OldHunter/BTTaskNode_OldHunter_Attack.h"

EBTNodeResult::Type UBTTaskNode_OldHunter_Attack::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, NodeMemory);

	EMonsterState StateValue = GetCurState<EMonsterState>(_OwnerComp);

	if (StateValue != EMonsterState::EMS_Attack)
	{
		return EBTNodeResult::Type::Failed;
	}

	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);

	if (false == Character->IsValidLowLevel())
	{
		return EBTNodeResult::Aborted;
	}

	if (Character->GetBBAIAnimInstance()->AttackMontage == nullptr)
	{
		return EBTNodeResult::Type::Failed;
	}
	Character->GetBBAIAnimInstance()->Montage_Play(Character->GetBBAIAnimInstance()->AttackMontage);

	ABBAIController* Controller = GetController<ABBAIController>(_OwnerComp);
	Controller->StopMovement();

	int Random = FMath::RandRange(1, 5);

	switch (Random)
	{
	case 1:
		Character->GetBBAIAnimInstance()->Montage_JumpToSection(TEXT("Attack1"));
		break;
	case 2:
		Character->GetBBAIAnimInstance()->Montage_JumpToSection(TEXT("Attack2"));
		break;
	case 3:
		Character->GetBBAIAnimInstance()->Montage_JumpToSection(TEXT("Attack3"));
		break;
	case 4:
		Character->GetBBAIAnimInstance()->Montage_JumpToSection(TEXT("Attack4"));
		break;
	case 5:
		Character->GetBBAIAnimInstance()->Montage_JumpToSection(TEXT("Attack5"));
		break;
	}

	return EBTNodeResult::InProgress;

}

void UBTTaskNode_OldHunter_Attack::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);

	if (Character->AttackEnd)
	{
		Character->AttackEnd = false;

		float Distance = GetDistanceToHunter(_OwnerComp);

		if (Distance < Character->CombatDistance)
		{
			ChangeState(_OwnerComp, EMonsterState::EMS_BackStep);
			return;
		}
		else
		{
			ChangeState(_OwnerComp, EMonsterState::EMS_Lull);
			return;
		}
	}
}
