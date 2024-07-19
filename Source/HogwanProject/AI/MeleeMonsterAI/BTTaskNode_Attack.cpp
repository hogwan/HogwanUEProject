// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MeleeMonsterAI/BTTaskNode_Attack.h"

EBTNodeResult::Type UBTTaskNode_Attack::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, NodeMemory);

	EMonsterState StateValue = GetCurState<EMonsterState>(_OwnerComp);

	if (StateValue != EMonsterState::EMS_Attack)
	{
		return EBTNodeResult::Type::Failed;
	}

	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);

	if (false == Character->IsValidLowLevel())
	{
		return EBTNodeResult::Aborted;
	}

	if (Character->GetBBAIAnimInstance()->AttackMontage == nullptr)
	{
		return EBTNodeResult::Type::Failed;
	}

	ABBAIController* Controller = GetController<ABBAIController>(_OwnerComp);
	Controller->StopMovement();
	
	EMonster MonsterEnum = GetMonsterEnum(_OwnerComp);

	switch (MonsterEnum)
	{
	case EMonster::EM_Zombie:
		ExecuteZombieAttack(_OwnerComp);
		break;
	case EMonster::EM_Parasite:
		ExecuteParasiteAttack(_OwnerComp);
		break;
	case EMonster::EM_Wolf:
		ExecuteParasiteAttack(_OwnerComp);
		break;
	case EMonster::EM_Mutant:
		ExecuteMutantAttack(_OwnerComp);
		break;
	default:
		break;
	}

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_Attack::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);
	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);

	if (Character)
	{
		if (Character->AttackEnd)
		{
			Character->AttackEnd = false;
			ChangeState(_OwnerComp, EMonsterState::EMS_Idle);
			return;
		}
	}
}

void UBTTaskNode_Attack::ExecuteZombieAttack(UBehaviorTreeComponent& _OwnerComp)
{
	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);
	Character->GetBBAIAnimInstance()->Montage_Play(Character->GetBBAIAnimInstance()->AttackMontage);

	int Random = FMath::RandRange(1, 2);

	switch (Random)
	{
	case 1:
		Character->GetBBAIAnimInstance()->Montage_JumpToSection(TEXT("Attack1"));
		break;
	case 2:
		Character->GetBBAIAnimInstance()->Montage_JumpToSection(TEXT("Attack2"));
		break;
	default:
		break;
	}
}

void UBTTaskNode_Attack::ExecuteParasiteAttack(UBehaviorTreeComponent& _OwnerComp)
{
	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);
	Character->GetBBAIAnimInstance()->Montage_Play(Character->GetBBAIAnimInstance()->AttackMontage);

	int Random = FMath::RandRange(1, 4);
	Character->GetAttribute()->Stamina -= 20.f;

	switch (Random)
	{
	case 1:
		Character->GetBBAIAnimInstance()->Montage_JumpToSection(TEXT("Attack1"));
		break;
	case 2:
		Character->GetBBAIAnimInstance()->Montage_JumpToSection(TEXT("Attack2"));
		break;
	case 3:
		Character->GetBBAIAnimInstance()->Montage_JumpToSection(TEXT("Attack3"));
		break;
	case 4:
		Character->GetBBAIAnimInstance()->Montage_JumpToSection(TEXT("Attack4"));
		break;
	default:
		break;
	}
}

void UBTTaskNode_Attack::ExecuteWolfAttack(UBehaviorTreeComponent& _OwnerComp)
{
	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);
	Character->GetBBAIAnimInstance()->Montage_Play(Character->GetBBAIAnimInstance()->AttackMontage);

	int Random = FMath::RandRange(1, 3);
	Character->GetAttribute()->Stamina -= 50.f;

	switch (Random)
	{
	case 1:
		Character->GetBBAIAnimInstance()->Montage_JumpToSection(TEXT("Attack1"));
		break;
	case 2:
		Character->GetBBAIAnimInstance()->Montage_JumpToSection(TEXT("Attack2"));
		break;
	case 3:
		Character->GetBBAIAnimInstance()->Montage_JumpToSection(TEXT("Attack3"));
		break;
	default:
		break;
	}
}

void UBTTaskNode_Attack::ExecuteMutantAttack(UBehaviorTreeComponent& _OwnerComp)
{
	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);
	Character->GetBBAIAnimInstance()->Montage_Play(Character->GetBBAIAnimInstance()->AttackMontage);

	int Random = FMath::RandRange(1, 4);
	Character->GetAttribute()->Stamina -= 20.f;

	switch (Random)
	{
	case 1:
		Character->GetBBAIAnimInstance()->Montage_JumpToSection(TEXT("Attack1"));
		break;
	case 2:
		Character->GetBBAIAnimInstance()->Montage_JumpToSection(TEXT("Attack2"));
		break;
	case 3:
		Character->GetBBAIAnimInstance()->Montage_JumpToSection(TEXT("Attack3"));
		break;
	case 4:
		Character->GetBBAIAnimInstance()->Montage_JumpToSection(TEXT("Attack4"));
		break;
	default:
		break;
	}
}

