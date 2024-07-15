// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/RangedMonsterAI/BTTaskNode_Ranged_Patrol.h"
#include "GameFramework/CharacterMovementComponent.h"

EBTNodeResult::Type UBTTaskNode_Ranged_Patrol::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, NodeMemory);

	EMonsterState StateValue = GetCurState<EMonsterState>(_OwnerComp);

	if (StateValue != EMonsterState::EMS_Patrol)
	{
		return EBTNodeResult::Type::Failed;
	}

	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);

	if (false == Character->IsValidLowLevel())
	{
		return EBTNodeResult::Aborted;
	}

	if (Character->GetBBAIAnimInstance()->WalkMontage == nullptr)
	{
		return EBTNodeResult::Type::Failed;
	}

	Character->PatrolPoints.Add(Character->GetActorLocation());
	Character->GetCharacterMovement()->MaxWalkSpeed = Character->WalkSpeed;

	Character->GetBBAIAnimInstance()->Montage_Play(Character->GetBBAIAnimInstance()->WalkMontage);

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_Ranged_Patrol::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	ABBAICharacter* Monster = GetActor<ABBAICharacter>(_OwnerComp);
	ABBAIController* MonsterController = GetController<ABBAIController>(_OwnerComp);

	if (!Monster || !MonsterController) return;

	int PatrolSize = Monster->PatrolPoints.Num();

	if (PatrolSize <= 1)
	{
		Monster->PatrolPoints.Pop();
		ChangeState(_OwnerComp, EMonsterState::EMS_Idle);
		return;
	}

	if (PerceiveInRange(_OwnerComp, Monster->PerceiveRange))
	{
		ChangeState(_OwnerComp,EMonsterState::EMS_Shoot);
		return;
	}


	if (MoveToPoint(_OwnerComp, Monster->PatrolPoints[Monster->PatrolNum % PatrolSize]))
	{
		Monster->PatrolNum++;
		ChangeState(_OwnerComp, EMonsterState::EMS_Idle);
		return;
	}
}
