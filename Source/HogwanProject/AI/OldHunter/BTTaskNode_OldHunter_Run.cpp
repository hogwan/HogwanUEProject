// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/OldHunter/BTTaskNode_OldHunter_Run.h"
#include "GameFramework/CharacterMovementComponent.h"

EBTNodeResult::Type UBTTaskNode_OldHunter_Run::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, NodeMemory);

	EMonsterState StateValue = GetCurState<EMonsterState>(_OwnerComp);

	if (StateValue != EMonsterState::EMS_Run)
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

	Character->GetCharacterMovement()->MaxWalkSpeed = Character->RunSpeed;
	Character->GetBBAIAnimInstance()->Montage_Play(Character->GetBBAIAnimInstance()->RunMontage);

	MoveToHunter(_OwnerComp, 10.f);

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_OldHunter_Run::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);
	RotateToHunter(_OwnerComp, _DeltaSeconds, 5.f);

	if (TargetInRange(_OwnerComp, Character->AttackRange))
	{
		ChangeState(_OwnerComp, EMonsterState::EMS_Attack);
		return;
	}

	float DashDistance = Character->DashAttackDistance;
	float Range = GetDistanceToHunter(_OwnerComp);

	if (Character->GetBBAIAnimInstance()->DashAttackMontage && abs(Range - DashDistance) < 50.f)
	{
		ChangeState(_OwnerComp, EMonsterState::EMS_DashAttack);
		return;
	}

	if (Range < Character->CombatDistance)
	{
		if (GetHunter()->GetCurActionState() == ECharacterActionState::ECAS_Attacking)
		{
			ChangeState(_OwnerComp, EMonsterState::EMS_Dodge);
			return;
		}
	}

}
