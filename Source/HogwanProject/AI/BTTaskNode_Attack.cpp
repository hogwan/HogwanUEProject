// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTaskNode_Attack.h"

EBTNodeResult::Type UBTTaskNode_Attack::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* NodeMemory)
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
	Character->GetBBAIAnimInstance()->Montage_Play(Character->GetBBAIAnimInstance()->AttackMontage);

	int Random = FMath::RandRange(1, 2);

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
	default:
		break;
	}

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_Attack::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);
	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);

	if (Character)
	{
		if (Character->AttackEnd)
		{
			Character->AttackEnd = false;
			ChangeState(_OwnerComp, EMonsterState::EMS_Idle);
			return;
		}
	}
}
