// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MeleeMonsterAI/BTTaskNode_Lull.h"
#include "ActorComponent/AttributeComponent.h"

EBTNodeResult::Type UBTTaskNode_Lull::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* NodeMemory)
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

	EMonster MonsterEnum = GetMonsterEnum(_OwnerComp);

	switch (MonsterEnum)
	{
	case EMonster::EM_Parasite:
		ExecuteParasiteLull(_OwnerComp);
		break;
	case EMonster::EM_Wolf:
		ExecuteWolfLull(_OwnerComp);
		break;
	case EMonster::EM_Mutant:
		ExecuteMutantLull(_OwnerComp);
		break;
	default:
		break;
	}

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_Lull::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);
	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);

	FVector HunterLocation = GetHunter()->GetActorLocation();
	FVector MonsterLocation = Character->GetActorLocation();

	float Distance = (HunterLocation - MonsterLocation).Size();

	if (Distance < 200.f)
	{
		Character->GetAttribute()->Stamina = Character->GetAttribute()->MaxStamina;
		ChangeState(_OwnerComp, EMonsterState::EMS_Idle);
		return;
	}

	if (Character->GetAttribute()->Stamina >= Character->GetAttribute()->MaxStamina)
	{
		Character->GetAttribute()->Stamina = Character->GetAttribute()->MaxStamina;
		ChangeState(_OwnerComp, EMonsterState::EMS_Idle);
		return;
	}

	EMonster MonsterEnum = GetMonsterEnum(_OwnerComp);

	switch (MonsterEnum)
	{
	case EMonster::EM_Parasite:
		UpdateParasiteLull(_OwnerComp, _DeltaSeconds);
		break;
	case EMonster::EM_Mutant:
		UpdateMutantLull(_OwnerComp, _DeltaSeconds);
		break;
	default:
		break;
	}

	RotateToHunter(_OwnerComp, _DeltaSeconds, Character->RotateSpeed);
	Character->GetAttribute()->Stamina += Character->StaminaRecoverSpeed * _DeltaSeconds;
}

void UBTTaskNode_Lull::ExecuteParasiteLull(UBehaviorTreeComponent& _OwnerComp)
{
	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);
	Character->GetBBAIAnimInstance()->Montage_Play(Character->GetBBAIAnimInstance()->LullMontage);

	int Random = FMath::RandRange(1, 2);

	switch (Random)
	{
	case 1:
		Character->GetBBAIAnimInstance()->Montage_JumpToSection("Right");
		Character->MonsterDir = EDir::Right;
		break;
	case 2:
		Character->GetBBAIAnimInstance()->Montage_JumpToSection("Left");
		Character->MonsterDir = EDir::Left;
		break;
	default:
		break;
	}
}

void UBTTaskNode_Lull::UpdateParasiteLull(UBehaviorTreeComponent& _OwnerComp, float _DeltaSeconds)
{
	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);
	Character->CurLullTime -= _DeltaSeconds;

	switch (Character->MonsterDir)
	{
	case EDir::Right:
		Character->AddActorWorldOffset(Character->GetActorRightVector() * Character->WalkSpeed * _DeltaSeconds);
		break;
	case EDir::Left:
		Character->AddActorWorldOffset(-Character->GetActorRightVector() * Character->WalkSpeed * _DeltaSeconds);
		break;
	case EDir::Back:
		Character->AddActorWorldOffset(-Character->GetActorForwardVector() * Character->WalkSpeed * _DeltaSeconds);
		break;
	case EDir::Forward:
		Character->AddActorWorldOffset(Character->GetActorForwardVector() * Character->WalkSpeed * _DeltaSeconds);
		break;
	}


	if (Character->CurLullTime < 0.f)
	{
		Character->CurLullTime = Character->MaxLullTime;
		ExecuteParasiteLull(_OwnerComp);
		return;
	}
}

void UBTTaskNode_Lull::ExecuteWolfLull(UBehaviorTreeComponent& _OwnerComp)
{
	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);
	Character->GetBBAIAnimInstance()->Montage_Play(Character->GetBBAIAnimInstance()->LullMontage);
}

void UBTTaskNode_Lull::ExecuteMutantLull(UBehaviorTreeComponent& _OwnerComp)
{
	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);
	Character->GetBBAIAnimInstance()->Montage_Play(Character->GetBBAIAnimInstance()->LullMontage);
}

void UBTTaskNode_Lull::UpdateMutantLull(UBehaviorTreeComponent& _OwnerComp, float _DeltaSeconds)
{
	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);

	Character->AddActorWorldOffset(-Character->GetActorForwardVector() * Character->WalkSpeed * _DeltaSeconds);
}
