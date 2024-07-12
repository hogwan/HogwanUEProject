// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/ANS_HunterTargetMotionWarping.h"
#include "Global/BBGameInstance.h"
#include "Character/Monster/Monster.h"
#include "Character/Hunter/Hunter.h"
#include "MotionWarpingComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UANS_HunterTargetMotionWarping::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	AActor* Owner = MeshComp->GetOwner();

	UBBGameInstance* GameInstance = Cast<UBBGameInstance>(MeshComp->GetOwner()->GetGameInstance());

	if (GameInstance)
	{
		Hunter = GameInstance->Hunter;
	}
	SelfMonster = Cast<AMonster>(MeshComp->GetOwner());

	if (SelfMonster)
	{
		MotionWarping = SelfMonster->GetMotionWarping();
	}
}

void UANS_HunterTargetMotionWarping::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if (!Hunter || !SelfMonster) return;

	FMotionWarpingTarget Target = {};
	Target.Name = FName("Hunter");

	FVector MonsterLocation = SelfMonster->GetActorLocation();
	MonsterLocation.Z = 0.f;

	FVector HunterLocation = Hunter->GetActorLocation();
	HunterLocation.Z = 0.f;


	FVector HunterToMonsterDir = MonsterLocation - HunterLocation;
	HunterToMonsterDir.Normalize();
	FVector TargetLocation = Hunter->GetActorLocation() + HunterToMonsterDir * 100.f;

	Target.Location = TargetLocation;

	FRotator TargetRotator = UKismetMathLibrary::FindLookAtRotation(SelfMonster->GetActorLocation(), Hunter->GetActorLocation());

	TargetRotator.Pitch = 0.f;
	TargetRotator.Roll = 0.f;

	Target.Rotation = TargetRotator;

	MotionWarping->AddOrUpdateWarpTarget(Target);
}
