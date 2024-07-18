// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MeleeMonsterAI/BTTaskNode_Run.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AI/BBAIController.h"

EBTNodeResult::Type UBTTaskNode_Run::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* NodeMemory)
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

	if (Character->GetBBAIAnimInstance()->RunMontage == nullptr)
	{
		return EBTNodeResult::Type::Failed;
	}

	Character->GetCharacterMovement()->MaxWalkSpeed = Character->RunSpeed;
	Character->GetBBAIAnimInstance()->Montage_Play(Character->GetBBAIAnimInstance()->RunMontage);

	MoveToHunter(_OwnerComp, 10.f);

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_Run::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);

	if (TargetInRange(_OwnerComp, 120.f))
	{
		ChangeState(_OwnerComp, EMonsterState::EMS_Attack);
		return;
	}

	float Range = GetDistanceToHunter(_OwnerComp);

	float DashDistance = Character->DashAttackDistance;

	if (Character->GetBBAIAnimInstance()->DashAttackMontage && abs(Range - DashDistance) < 50.f)
	{
		ChangeState(_OwnerComp, EMonsterState::EMS_DashAttack);
		return;
	}
}
