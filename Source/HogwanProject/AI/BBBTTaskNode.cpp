// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BBBTTaskNode.h"
#include "Kismet/GameplayStatics.h"
#include "Character/Hunter/BBPlayerController.h"
#include "Character/Hunter/Hunter.h"
#include "Kismet/KismetMathLibrary.h"
#include "AIController.h"

UBBBTTaskNode::UBBBTTaskNode()
{
	bNotifyTick = true;
}

void UBBBTTaskNode::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	if (EMonsterState::EMS_Unable == GetCurState<EMonsterState>(_OwnerComp))
	{
		ChangeState(_OwnerComp, EMonsterState::EMS_Unable);
		return;
	}
}

AActor* UBBBTTaskNode::GetActor(UBehaviorTreeComponent& _OwnerComp)
{
	UObject* Object = _OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("SelfActor"));
	return Cast<AActor>(Object);
}

uint8 UBBBTTaskNode::GetCurState(UBehaviorTreeComponent& _OwnerComp)
{
	return _OwnerComp.GetBlackboardComponent()->GetValueAsEnum(TEXT("StateValue"));
}

AHunter* UBBBTTaskNode::GetHunter()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	ABBPlayerController* HunterController = Cast<ABBPlayerController>(PlayerController);

	AHunter* Hunter = Cast<AHunter>(HunterController->GetPawn());

	return Hunter;
}

void UBBBTTaskNode::ChangeState(UBehaviorTreeComponent& _OwnerComp, uint8 _StateChange)
{
	StatusReset(_OwnerComp);
	_OwnerComp.GetBlackboardComponent()->SetValueAsEnum(TEXT("StateValue"), _StateChange);
	FinishLatentTask(_OwnerComp, EBTNodeResult::Failed);
}

bool UBBBTTaskNode::TargetInRange(UBehaviorTreeComponent& _OwnerComp, float _Range)
{
	AHunter* Hunter = GetHunter();
	AActor* Self = GetActor<AActor>(_OwnerComp);

	if (!Hunter || !Self) return false;

	FVector TargetPosition = Hunter->GetActorLocation();
	TargetPosition.Z = 0.f;

	FVector CurPosition = Self->GetActorLocation();
	CurPosition.Z = 0.f;

	float Range = (TargetPosition - CurPosition).Size();

	if (Range < _Range)
	{
		return true;
	}
	else return false;
}

float UBBBTTaskNode::BetweenAngleToDegree(UBehaviorTreeComponent& _OwnerComp)
{
	AHunter* Hunter = GetHunter();
	AActor* Self = GetActor<AActor>(_OwnerComp);

	if (!Hunter || !Self) return -99999.f;

	FVector StartVector = GetActor<AActor>(_OwnerComp)->GetActorForwardVector();
	StartVector.Z = 0.f;
	StartVector.Normalize();

	FVector EndVector = GetHunter()->GetActorLocation() - GetActor<AActor>(_OwnerComp)->GetActorLocation();
	EndVector.Z = 0.f;
	EndVector.Normalize();

	float DotScala = UKismetMathLibrary::Dot_VectorVector(StartVector, EndVector);

	float Angle = UKismetMathLibrary::Acos(DotScala);

	return FMath::RadiansToDegrees(Angle);
}

bool UBBBTTaskNode::DecideRotationDirection(UBehaviorTreeComponent& _OwnerComp)
{
	FVector StartVector = GetActor<AActor>(_OwnerComp)->GetActorForwardVector();
	StartVector.Z = 0.f;
	StartVector.Normalize();

	FVector EndVector = GetHunter()->GetActorLocation() - GetActor<AActor>(_OwnerComp)->GetActorLocation();
	EndVector.Z = 0.f;
	EndVector.Normalize();

	FVector CrossVector = UKismetMathLibrary::Cross_VectorVector(StartVector, EndVector);

	if (CrossVector.Z > 0.f)
	{
		return true;
	}
	else return false;
}

void UBBBTTaskNode::StatusReset(UBehaviorTreeComponent& _OwnerComp)
{
	ABBAICharacter* Monster = GetActor<ABBAICharacter>(_OwnerComp);
	if (Monster)
	{
		Monster->IdleAcc = Monster->IdleTime;
	}
}

void UBBBTTaskNode::MoveToHunter(UBehaviorTreeComponent& _OwnerComp, float SuccessRange)
{
	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);

	FAIMoveRequest AIMoveRequest;
	AIMoveRequest.SetGoalActor(GetHunter());
	AIMoveRequest.SetAcceptanceRadius(SuccessRange);

	ABBAIController* Controller = GetController<ABBAIController>(_OwnerComp);
	Controller->MoveToActor(GetHunter(), SuccessRange);
}

void UBBBTTaskNode::MoveToPoint(UBehaviorTreeComponent& _OwnerComp, AActor* TargetLocation, float SuccessRange)
{
	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);

	ABBAIController* Controller = GetController<ABBAIController>(_OwnerComp);
	Controller->MoveToActor(TargetLocation, SuccessRange);

}

float UBBBTTaskNode::GetDistanceToHunter(UBehaviorTreeComponent& _OwnerComp)
{
	AHunter* Hunter = GetHunter();
	AActor* Self = GetActor<AActor>(_OwnerComp);

	if (!Hunter || !Self) return false;

	FVector TargetPosition = Hunter->GetActorLocation();
	TargetPosition.Z = 0.f;

	FVector CurPosition = Self->GetActorLocation();
	CurPosition.Z = 0.f;

	float Range = (TargetPosition - CurPosition).Size();

	return Range;
}

EMonster UBBBTTaskNode::GetMonsterEnum(UBehaviorTreeComponent& _OwnerComp)
{
	AMonster* Monster = GetActor<AMonster>(_OwnerComp);

	EMonster MonsterEnum = Monster->MonsterEnum;

	return MonsterEnum;
}

void UBBBTTaskNode::RotateToHunter(UBehaviorTreeComponent& _OwnerComp, float DeltaTime)
{
	ABBAICharacter* Character = GetActor<ABBAICharacter>(_OwnerComp);
	
	FVector AIPos = Character->GetActorLocation();
	FVector HunterPos = GetHunter()->GetActorLocation();

	FVector ForwardVector = Character->GetActorForwardVector();
	FVector TargetVector = HunterPos - AIPos;



	FRotator FindRot = UKismetMathLibrary::FindLookAtRotation(AIPos, HunterPos);
	FRotator StartRot = Character->GetActorRotation();
	FRotator Result = UKismetMathLibrary::RInterpTo(StartRot, FindRot, DeltaTime, 5.f);

	FRotator ResultRotation = FRotator(0.f, Result.Yaw, 0.f);

	Character->SetActorRotation(ResultRotation);
}

AController* UBBBTTaskNode::GetController(UBehaviorTreeComponent& _OwnerComp)
{
	return Cast<AController>(_OwnerComp.GetOwner());
}