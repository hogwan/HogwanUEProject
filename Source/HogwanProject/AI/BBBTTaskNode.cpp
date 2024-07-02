// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BBBTTaskNode.h"
#include "Kismet/GameplayStatics.h"
#include "Character/Hunter/BBPlayerController.h"
#include "Character/Hunter/Hunter.h"
#include "Kismet/KismetMathLibrary.h"

UBBBTTaskNode::UBBBTTaskNode()
{
	bNotifyTick = true;
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
	_OwnerComp.GetBlackboardComponent()->SetValueAsEnum(TEXT("StateValue"), _StateChange);
	FinishLatentTask(_OwnerComp, EBTNodeResult::Failed);
}

bool UBBBTTaskNode::PerceiveInRange(UBehaviorTreeComponent& _OwnerComp, float PerceiveRange)
{
	AHunter* Hunter = GetHunter();
	AActor* Self = GetActor<AActor>(_OwnerComp);

	if (!Hunter || !Self) return false;

	FVector TargetPosition = Hunter->GetActorLocation();
	TargetPosition.Z = 0.f;

	FVector CurPosition = Self->GetActorLocation();
	CurPosition.Z = 0.f;

	float Range = (TargetPosition - CurPosition).Size();

	if (Range < PerceiveRange)
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

void UBBBTTaskNode::TimeReset(UBehaviorTreeComponent& _OwnerComp)
{
	ABBAICharacter* Monster = GetActor<ABBAICharacter>(_OwnerComp);
	if (Monster)
	{
		Monster->IdleAcc = Monster->IdleTime;
	}
}

AController* UBBBTTaskNode::GetController(UBehaviorTreeComponent& _OwnerComp)
{
	return Cast<AController>(_OwnerComp.GetOwner());
}