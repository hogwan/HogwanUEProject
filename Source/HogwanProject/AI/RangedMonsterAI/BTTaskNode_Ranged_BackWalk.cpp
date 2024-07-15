// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/RangedMonsterAI/BTTaskNode_Ranged_BackWalk.h"
#include "GameFramework/CharacterMovementComponent.h"

EBTNodeResult::Type UBTTaskNode_Ranged_BackWalk::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, NodeMemory);

	EMonsterState StateValue = GetCurState<EMonsterState>(_OwnerComp);

	if (StateValue != EMonsterState::EMS_BackWalk)
	{
		return EBTNodeResult::Type::Failed;
	}

	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);

	if (false == Character->IsValidLowLevel())
	{
		return EBTNodeResult::Aborted;
	}

	ABBAIController* MonsterController = GetController<ABBAIController>(_OwnerComp);

	if (Character->GetBBAIAnimInstance()->BackWalkMontage == nullptr)
	{
		return EBTNodeResult::Type::Failed;
	}

	Character->GetBBAIAnimInstance()->Montage_Play(Character->GetBBAIAnimInstance()->BackWalkMontage);

	Character->GetCharacterMovement()->MaxWalkSpeed = Character->WalkSpeed;

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_Ranged_BackWalk::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	ABBAICharacter* Monster = GetActor<ABBAICharacter>(_OwnerComp);
	ABBAIController* MonsterController = GetController<ABBAIController>(_OwnerComp);
	if (!Monster) return;
	
	Monster->AddMovementInput(-Monster->GetActorForwardVector());
	float Distance = (Monster->GetActorLocation() - GetHunter()->GetActorLocation()).Size();

	if (Distance <= Monster->PunchDistance)
	{
		ChangeState(_OwnerComp, EMonsterState::EMS_Attack);
		return;
	}

	if (Distance > Monster->BackWalkDistance)
	{
		ChangeState(_OwnerComp, EMonsterState::EMS_Shoot);
		return;
	}
}
