// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BBBTTaskNode.h"
#include "Kismet/GameplayStatics.h"
#include "Global/BBPlayerController.h"
#include "Hunter/Hunter.h"

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

AActor* UBBBTTaskNode::GetTarget(UBehaviorTreeComponent& _OwnerComp, float _Range, uint8 _TargetGroup, bool _ZIgnore /*= true*/)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	ABBPlayerController* HunterController = Cast<ABBPlayerController>(PlayerController);

	return Cast<AHunter>(HunterController->GetOwner());
}

AActor* UBBBTTaskNode::CheckTarget(UBehaviorTreeComponent& _OwnerComp, float _Range, uint8 Target, bool _ZIgnore /*= true*/)
{
	AActor* TargetActor = GetTarget(_OwnerComp, _Range, Target);

	if (nullptr == TargetActor)
	{
		_OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), nullptr);
		return nullptr;
	}

	_OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), TargetActor);

	return TargetActor;
}

void UBBBTTaskNode::ChangeState(UBehaviorTreeComponent& _OwnerComp, uint8 _StateChange)
{
	_OwnerComp.GetBlackboardComponent()->SetValueAsEnum(TEXT("StateValue"), _StateChange);
	FinishLatentTask(_OwnerComp, EBTNodeResult::Failed);
}

AController* UBBBTTaskNode::GetController(UBehaviorTreeComponent& _OwnerComp)
{
	return Cast<AController>(_OwnerComp.GetOwner());
}