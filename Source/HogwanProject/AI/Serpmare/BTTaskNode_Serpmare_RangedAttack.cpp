// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Serpmare/BTTaskNode_Serpmare_RangedAttack.h"

EBTNodeResult::Type UBTTaskNode_Serpmare_RangedAttack::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, NodeMemory);

	EMonsterState StateValue = GetCurState<EMonsterState>(_OwnerComp);

	if (StateValue != EMonsterState::EMS_Shoot)
	{
		return EBTNodeResult::Type::Failed;
	}

	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);

	if (false == Character->IsValidLowLevel())
	{
		return EBTNodeResult::Aborted;
	}

	if (Character->GetBBAIAnimInstance()->ShootMontage == nullptr)
	{
		return EBTNodeResult::Type::Failed;
	}

	Character->GetBBAIAnimInstance()->Montage_Play(Character->GetBBAIAnimInstance()->ShootMontage);

	int Random = FMath::RandRange(1, 3);

	switch (Random)
	{
	case 1:
		Character->GetBBAIAnimInstance()->Montage_JumpToSection(TEXT("RangedPattern1"));
		break;
	case 2:
		Character->GetBBAIAnimInstance()->Montage_JumpToSection(TEXT("RangedPattern2"));
		break;
	case 3:
		Character->GetBBAIAnimInstance()->Montage_JumpToSection(TEXT("RangedPattern3"));
		break;
	}

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_Serpmare_RangedAttack::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);

	if (Character && Character->AttackEnd)
	{
		Character->AttackEnd = false;
		ChangeState(_OwnerComp, EMonsterState::EMS_PatternTerm);
		return;
	}
}
