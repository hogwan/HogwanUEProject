// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ANS_LeftJumpMotionWarping.generated.h"

/**
 * 
 */
UCLASS()
class HOGWANPROJECT_API UANS_LeftJumpMotionWarping : public UAnimNotifyState
{
	GENERATED_BODY()

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;

	class AMonster* SelfMonster;
	class UMotionWarpingComponent* MotionWarping;
};
