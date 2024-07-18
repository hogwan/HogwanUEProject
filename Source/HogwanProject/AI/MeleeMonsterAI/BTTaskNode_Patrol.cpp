// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MeleeMonsterAI/BTTaskNode_Patrol.h"
#include "GameFrameWork/CharacterMovementComponent.h"

EBTNodeResult::Type UBTTaskNode_Patrol::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* NodeMemory)
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

	Character->GetCharacterMovement()->MaxWalkSpeed = Character->WalkSpeed;

	Character->GetBBAIAnimInstance()->Montage_Play(Character->GetBBAIAnimInstance()->WalkMontage);

	int PatrolSize = Character->PatrolPoints.Num();

	MoveToPoint(_OwnerComp, Character->PatrolPoints[Character->PatrolNum % PatrolSize], 10.f);

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_Patrol::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	ABBAICharacter* Monster = GetActor<ABBAICharacter>(_OwnerComp);
	ABBAIController* MonsterController = GetController<ABBAIController>(_OwnerComp);

	if (!Monster || !MonsterController) return;

	int PatrolSize = Monster->PatrolPoints.Num();
	FVector TargetLocation = Monster->PatrolPoints[Monster->PatrolNum % PatrolSize]->GetActorLocation();
	TargetLocation.Z = 0.f;

	FVector MonsterLocation = Monster->GetActorLocation();
	MonsterLocation.Z = 0.f;

	float Distance = (TargetLocation - MonsterLocation).Size();


	if (PatrolSize <= 1)
	{
		Monster->PatrolPoints.Pop();
		ChangeState(_OwnerComp,EMonsterState::EMS_Idle);
		return;
	}

	if (Monster->PerceiveHunter)
	{
		if (BetweenAngleToDegree(_OwnerComp) > 90.f)
		{
			Monster->PatrolPoints.Pop();
			Monster->PatrolNum = 0;
			ChangeState(_OwnerComp, EMonsterState::EMS_Turn);
			return;
		}

		Monster->PatrolPoints.Pop();
		Monster->PatrolNum = 0;
		ChangeState(_OwnerComp, EMonsterState::EMS_Perceive);
		return;
	}
	

	if (Distance < 50.f)
	{
		Monster->PatrolNum++;
		ChangeState(_OwnerComp, EMonsterState::EMS_Idle);
		return;
	}
}
