// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/OldHunter/BTTaskNode_OldHunter_Backwalk.h"
#include "GameFramework/CharacterMovementComponent.h"

EBTNodeResult::Type UBTTaskNode_OldHunter_Backwalk::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* NodeMemory)
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

	if (Character->GetBBAIAnimInstance()->BackWalkMontage == nullptr)
	{
		return EBTNodeResult::Type::Failed;
	}

	Character->GetBBAIAnimInstance()->Montage_Play(Character->GetBBAIAnimInstance()->BackWalkMontage);
	Character->GetCharacterMovement()->MaxWalkSpeed = Character->RunSpeed;

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_OldHunter_Backwalk::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);

	Character->AddMovementInput(-Character->GetActorForwardVector());
	RotateToHunter(_OwnerComp, _DeltaSeconds, 5.f);

	Character->WaitAcc -= _DeltaSeconds;

	if (Character->WaitAcc < 0.f)
	{
		Character->WaitAcc = Character->WaitTime;

		float Distance = GetDistanceToHunter(_OwnerComp);

		if (Distance < Character->CombatDistance)
		{
			ChangeState(_OwnerComp, EMonsterState::EMS_Attack);
			return;
		}
		else if(Distance > 400.f)
		{
			ChangeState(_OwnerComp, EMonsterState::EMS_Shoot);
			return;
		}
	}
}
