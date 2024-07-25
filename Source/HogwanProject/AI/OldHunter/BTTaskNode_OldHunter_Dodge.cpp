// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/OldHunter/BTTaskNode_OldHunter_Dodge.h"

EBTNodeResult::Type UBTTaskNode_OldHunter_Dodge::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, NodeMemory);

	EMonsterState StateValue = GetCurState<EMonsterState>(_OwnerComp);

	if (StateValue != EMonsterState::EMS_Dodge)
	{
		return EBTNodeResult::Type::Failed;
	}

	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);

	if (false == Character->IsValidLowLevel())
	{
		return EBTNodeResult::Aborted;
	}

	if (Character->GetBBAIAnimInstance()->DodgeMontage == nullptr)
	{
		return EBTNodeResult::Type::Failed;
	}
	Character->GetBBAIAnimInstance()->Montage_Play(Character->GetBBAIAnimInstance()->DodgeMontage);

	ABBAIController* Controller = GetController<ABBAIController>(_OwnerComp);
	Controller->StopMovement();

	int Random = FMath::RandRange(1, 3);

	switch (Random)
	{
	case 1:
		Character->GetBBAIAnimInstance()->Montage_JumpToSection(TEXT("DodgeFront"));
		break;
	case 2:
		Character->GetBBAIAnimInstance()->Montage_JumpToSection(TEXT("DodgeRight"));
		break;
	case 3:
		Character->GetBBAIAnimInstance()->Montage_JumpToSection(TEXT("DodgeLeft"));
		break;
	}

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_OldHunter_Dodge::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);

	if (Character->DodgeEnd)
	{
		Character->DodgeEnd = false;

		ChangeState(_OwnerComp, EMonsterState::EMS_Run);
		return;
	}
}
