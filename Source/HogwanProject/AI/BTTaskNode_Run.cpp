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

	Character->GetCharacterMovement()->MaxWalkSpeed = 400.f;
	Character->GetBBAIAnimInstance()->Montage_Play(Character->GetBBAIAnimInstance()->RunMontage);


	return EBTNodeResult::InProgress;
}

void UBTTaskNode_Run::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);

	if (MoveToHunter(_OwnerComp, 80.f))
	{
		ChangeState(_OwnerComp, EMonsterState::EMS_Attack);
		return;
	}
}
