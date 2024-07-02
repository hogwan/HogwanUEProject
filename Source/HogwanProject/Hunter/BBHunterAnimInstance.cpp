// Fill out your copyright notice in the Description page of Project Settings.


#include "Hunter/BBHunterAnimInstance.h"
#include "Hunter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UBBHunterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Hunter = Cast<AHunter>(TryGetPawnOwner());
	if (Hunter)
	{
		HunterMovement = Hunter->GetCharacterMovement();
	}
}

void UBBHunterAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (HunterMovement)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(HunterMovement->Velocity);
		MoveRotDegree = Hunter->MoveRotDegree;
	}
}