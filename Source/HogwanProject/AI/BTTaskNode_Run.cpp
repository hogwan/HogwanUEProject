// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTaskNode_Run.h"
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

	Character->ChangeAnimation(EMonsterAnimation::EMA_Run);

	Character->GetCharacterMovement()->MaxWalkSpeed = 400.f;

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_Run::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	ABBAIController* MonsterController = GetController<ABBAIController>(_OwnerComp);

	MonsterController->MoveToActor(GetHunter());
	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);

	if (PerceiveInRange(_OwnerComp,Character->AttackRange))
	{
		MonsterController->StopMovement();
		ChangeState(_OwnerComp, EMonsterState::EMS_Attack);
		return;
	}
}
