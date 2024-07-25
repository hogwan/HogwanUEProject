// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/OldHunter/BTTaskNode_OldHunter_Lull.h"
#include "GameFramework/CharacterMovementComponent.h"

EBTNodeResult::Type UBTTaskNode_OldHunter_Lull::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, NodeMemory);

	EMonsterState StateValue = GetCurState<EMonsterState>(_OwnerComp);

	if (StateValue != EMonsterState::EMS_Lull)
	{
		return EBTNodeResult::Type::Failed;
	}

	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);

	if (false == Character->IsValidLowLevel())
	{
		return EBTNodeResult::Aborted;
	}

	if (Character->GetBBAIAnimInstance()->LullMontage == nullptr)
	{
		return EBTNodeResult::Type::Failed;
	}

	Character->GetBBAIAnimInstance()->Montage_Play(Character->GetBBAIAnimInstance()->LullMontage);
	Character->GetCharacterMovement()->MaxWalkSpeed = Character->RunSpeed;

	int Random = FMath::RandRange(1, 2);

	switch (Random)
	{
	case 1:
		Character->GetBBAIAnimInstance()->Montage_JumpToSection("RightStrafe");
		Character->MonsterDir = EDir::Right;
		break;
	case 2:
		Character->GetBBAIAnimInstance()->Montage_JumpToSection("LeftStrafe");
		Character->MonsterDir = EDir::Left;
		break;
	default:
		break;
	}
	

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_OldHunter_Lull::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);
	ABBAIController* Controller = GetController<ABBAIController>(_OwnerComp);

	Character->CurLullTime -= _DeltaSeconds;

	float Distance = GetDistanceToHunter(_OwnerComp);

	if (Distance < Character->CombatDistance)
	{
		Character->CurLullTime = Character->MaxLullTime;
		ChangeState(_OwnerComp, EMonsterState::EMS_Dodge);
		return;
	}
	
	if (Character->CurLullTime < 0.f)
	{
		Character->CurLullTime = Character->MaxLullTime;
		ChangeState(_OwnerComp, EMonsterState::EMS_Run);
		return;
	}

	RotateToHunter(_OwnerComp, _DeltaSeconds, 5.f);

	switch (Character->MonsterDir)
	{
	case EDir::Right:
		Character->AddMovementInput(Character->GetActorRightVector());
		break;
	case EDir::Left:
		Character->AddMovementInput(-Character->GetActorRightVector());
		break;
	}


}
