// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTaskNode_Perceive.h"
#include "AI/BBAIAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"

EBTNodeResult::Type UBTTaskNode_Perceive::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, NodeMemory);

	EMonsterState StateValue = GetCurState<EMonsterState>(_OwnerComp);

	if (StateValue != EMonsterState::EMS_Perceive)
	{
		return EBTNodeResult::Type::Failed;
	}

	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);

	if (false == Character->IsValidLowLevel())
	{
		return EBTNodeResult::Aborted;
	}

	Character->ChangeAnimation(EMonsterAnimation::EMA_Perceive);

	FVector ActorPos = Character->GetActorLocation();
	ActorPos.Z = 0.f;

	FVector TargetPos = GetHunter()->GetActorLocation();
	TargetPos.Z = 0.f;

	FRotator FindRotator = UKismetMathLibrary::FindLookAtRotation(ActorPos, TargetPos);
	Character->SetActorRotation(FindRotator);
	Character->PerceiveHunter = true;
	Character->GetBBAIAnimInstance()->Montage_Play(Character->GetBBAIAnimInstance()->PerceiveMontage);

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_Perceive::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);
	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);
	if (Character)
	{
		if (Character->PerceiveEnd)
		{
			Character->PerceiveEnd = false;
			ChangeState(_OwnerComp, EMonsterState::EMS_Run);
			return;
		}
	}
}
