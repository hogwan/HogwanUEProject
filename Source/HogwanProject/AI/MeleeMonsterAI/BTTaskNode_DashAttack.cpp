// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MeleeMonsterAI/BTTaskNode_DashAttack.h"

EBTNodeResult::Type UBTTaskNode_DashAttack::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, NodeMemory);

	EMonsterState StateValue = GetCurState<EMonsterState>(_OwnerComp);

	if (StateValue != EMonsterState::EMS_DashAttack)
	{
		return EBTNodeResult::Type::Failed;
	}

	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);

	if (false == Character->IsValidLowLevel())
	{
		return EBTNodeResult::Aborted;
	}

	if (Character->GetBBAIAnimInstance()->DashAttackMontage == nullptr)
	{
		ChangeState(_OwnerComp, EMonsterState::EMS_Idle);
		return EBTNodeResult::Type::Failed;
	}

	EMonster MonsterEnum = GetMonsterEnum(_OwnerComp);

	switch (MonsterEnum)
	{
	case EMonster::EM_Parasite:
		ExecuteParasiteDashAttack(_OwnerComp);
		break;
	case EMonster::EM_Wolf:
		ExecuteWolfDashAttack(_OwnerComp);
		break;
	default:
		break;
	}

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_DashAttack::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
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

void UBTTaskNode_DashAttack::ExecuteParasiteDashAttack(UBehaviorTreeComponent& _OwnerComp)
{
	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);
	Character->GetBBAIAnimInstance()->Montage_Play(Character->GetBBAIAnimInstance()->DashAttackMontage);
	Character->CurStamina -= 50.f;
}

void UBTTaskNode_DashAttack::ExecuteWolfDashAttack(UBehaviorTreeComponent& _OwnerComp)
{
	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);
	Character->GetBBAIAnimInstance()->Montage_Play(Character->GetBBAIAnimInstance()->DashAttackMontage);
	Character->CurStamina -= 50.f;
}
