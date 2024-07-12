// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/ANS_RightJumpMotionWarping.h"
#include "Character/Monster/Monster.h"
#include "MotionWarpingComponent.h"

void UANS_RightJumpMotionWarping::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	AActor* Owner = MeshComp->GetOwner();

	SelfMonster = Cast<AMonster>(MeshComp->GetOwner());

	if (SelfMonster)
	{
		MotionWarping = SelfMonster->GetMotionWarping();
	}
}

void UANS_RightJumpMotionWarping::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if (!SelfMonster) return;

	FMotionWarpingTarget Target = {};
	Target.Name = FName("RightStepPosition");

	FVector TargetLocation = SelfMonster->GetActorLocation() + SelfMonster->GetActorRightVector() * SelfMonster->JumpDistance;

	Target.Location = TargetLocation;

	MotionWarping->AddOrUpdateWarpTarget(Target);
}
